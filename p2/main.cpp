//main.cpp
//Embuldeniya, Shihan
//cembuldeniyaarachchi

#include <iostream>
#include <string>

#include "meme.h"

using namespace std;

int main(){
    string sortMethod;
    if (!getline(cin, sortMethod)){
        return 0;
    }

    if (sortMethod != "category" && sortMethod != "rating"){
        cerr << sortMethod << " is not a legal sorting method, giving up." << endl;
        return 1;
    }

    const int MEMES_MAX = 100;
    Meme *memes[MEMES_MAX];
    int num_memes = 0;

    string url, description, category;
    double rating;

    while (getline(cin, url)){
        if (!getline (cin, description)){
            break;
        }
        if (!getline (cin, category)){
            break;
        }
        if (!(cin >> rating)){
            break;
        }
        cin.ignore();

        if (num_memes >= MEMES_MAX){
            cerr << "Too many memes, giving up." << endl;
            for (int i = 0; i < num_memes; i++){
                delete memes[i];
            }
            return 1;
        }

        // Meme *m = new Meme(url, description, category, rating);
        // m->print();
        // delete m;
        memes[num_memes] = new Meme(url, description, category, rating);
        num_memes++;
    }
    for (int last = num_memes - 1; last > 0; last--){
        for (int i = 0; i < last; i++){
            bool swap_need = false;
            if (sortMethod == "category"){
                if (memes[i]->category_goes_after(memes[i + 1])){
                    swap_need = true;
                }
            }
            else {
                if (memes[i]->rating_goes_after(memes[i + 1])){
                    swap_need = true;
                }
            }
            if (swap_need){
                Meme *temp = memes[i];
                memes[i] = memes[i + 1];
                memes[i + 1] = temp;
            }
        }
    }

    for (int i = 0; i < num_memes; i++){
        memes[i]->print();
    }
    for (int i = 0; i < num_memes; i++){
        delete memes[i];
    }

    return 0;
}