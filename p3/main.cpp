// meme.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include <iostream>
#include <string>
#include "meme.h"
#include "mlist.h"

using namespace std;

int main() {
    Mlist memes;                
    string command;

    while (getline(cin, command)) {
        if (command == "insert") {
            string url, description, category;
            double rating;
            
            if (getline(cin, url) && getline(cin, description) && getline(cin, category) && (cin >> rating)){
                cin.ignore();
                
                Meme* m = new Meme(url, description, category, rating);
                if (!memes.insert(m)) {
                    cerr << "Could not insert meme URL <" << url << "> already in list." << endl;
                    delete m;
                }
            } 
            else {
                return 0;
            }
        }
        else if (command == "print") {
            memes.print();  
        }
        else if (command == "length") {
            cout << memes.length() << endl;  
        }
        else if (command == "lookup") {
            string url;
            if (!getline(cin, url)){
                return 0;
            } 
            Meme* found = memes.lookup(url);
            if (found) {
                found->print();
            }
            else {
                cerr << "URL <" << url << "> not in list, lookup failed." << endl;
            }
        }
        else if (command == "remove") {
            string url;
            if (!getline(cin, url)){
                return 0;
            }
            if (!memes.remove(url)){
                cerr << "URL <" << url << "> not in list, could not delete." << endl;
            }
        }
        else if (command == "display") {
            int index;
            if (!(cin >> index)){
                return 0;
            }
            cin.ignore(); 

            if (!memes.display_index(index)) {
                cerr << "List does not contain a meme at index = <" << index << ">." << endl;
            }
        }
        else {
            cerr << "<" << command << "> is not a legal command, giving up." << endl;
            return 1;
        }
    }

    return 0;
}
