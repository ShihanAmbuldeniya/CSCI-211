//chart.cpp
//Embuldeniya, Shihan
//cembuldeniyaarachch

#include <iostream>
using namespace std;

int main (){
    const int MAX = 100;
    int valuesArr[MAX];
    
    int count = 0;
    int usrNums;

    for (int i = 0; i < MAX; i++){
        cin >> usrNums;
        if (usrNums == 0){
            break;
        }
        else {
            valuesArr[i] = usrNums;
            count++;
        }
    }

    int highestVal;
    highestVal = valuesArr[0];
    for (int i = 1; i < count; i++){
        if (valuesArr[i] > highestVal){
            highestVal = valuesArr[i];
        }
    }

    for (int y = highestVal; y >= 1; y--){ //decrementing rows
        for (int x = 0; x < count; x++){
            if (valuesArr[x] >= y){
                cout << "*";
            }
            else {
                cout << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}