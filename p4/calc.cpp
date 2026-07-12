// calc.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include "dstack.h"

using namespace std;

void handleError() {
    cerr << "Error: Invalid expression." << endl;
    exit(1);
}

int main(){
    Dstack stack;
    double number;
    double left;
    double right;
    double result;
    char operation;
    int nextChar;

    while (true){
        nextChar = cin.peek(); //looking at next character 

        if (nextChar == EOF){
            break; //end of input
        }
        
        // Skip spaces, tabs, newlines
        if (isspace(nextChar)) {
            cin.ignore(1);
            continue;
        }
                
        // Checking if it starts with digit or '.'
        // or starts with '+' or '-' followed by digit or '.'
        if (isdigit(nextChar) || nextChar == '.') {
            // Plain positive number
            if (!(cin >> number)) {
                handleError();
            }
            stack.push(number);

            //Checking the after number character
            int afterNumber = cin.peek();
            if (afterNumber != EOF
                && !isspace(afterNumber)
                && afterNumber != '+'
                && afterNumber != '-'
                && afterNumber != '*'
                && afterNumber != '/'
                && afterNumber != '^') {
                handleError(); 
            }
            continue;
        } 
        else if (nextChar == '-') {
            char signChar = cin.get();  // getting the '-'
            int afterMinus = cin.peek();
            
            if (isdigit(afterMinus) || afterMinus == '.') {
                // if it's a negative number like -2 or -3.5
                cin.putback(signChar); // put back the '-'
                if (!(cin >> number)) {
                    handleError();
                }
                stack.push(number);  

                //Checking the after number character
                //like in t14, -1.2.3 +
                int afterNumber = cin.peek();
                if (afterNumber != EOF
                    && !isspace(afterNumber)
                    && afterNumber != '+'
                    && afterNumber != '-'
                    && afterNumber != '*'
                    && afterNumber != '/'
                    && afterNumber != '^') {
                    handleError(); 
                }
                continue;
            } 
            else {
                // it's a subtraction operator
                cin.putback(signChar); 
            }
        }
        else if (nextChar == '+') {
            char signChar = cin.get();  // getting the '+'
            int afterPlus = cin.peek();
            
            if (isdigit(afterPlus) || afterPlus == '.') {
                // if it's a positive number like +2 or +3.5
                cin.putback(signChar); // put back the '+'
                if (!(cin >> number)) {
                    handleError();
                }
                stack.push(number);  // Keeping it positive

                //Checking the after number character
                int afterNumber = cin.peek();
                if (afterNumber != EOF
                    && !isspace(afterNumber)
                    && afterNumber != '+'
                    && afterNumber != '-'
                    && afterNumber != '*'
                    && afterNumber != '/'
                    && afterNumber != '^') {
                    handleError(); 
                }
                continue;
            } 
            else {
                // it's an addition operator
                cin.putback(signChar); 
            }
        }

        // cin >> operation;
        operation = cin.get(); //getting the operator

        if (operation == '+' || operation == '-' || operation == '*' || operation == '/' || operation == '^') {
        // Pop two numbers from stack
            if (!stack.pop(right)) {
                handleError();
            }
            if (!stack.pop(left)) {
                handleError();
            }

            // Performing operation
            if (operation == '+') {
                result = left + right;
            } 
            else if (operation == '-') {
                result = left - right;
            } 
            else if (operation == '*') {
                result = left * right;
            } 
            else if (operation == '/') {
                if (right == 0.0) {
                    handleError();
                }
                result = left / right;
            } 
            else if (operation == '^') {
                if (left == 0.0 && right == 0.0) {
                    result = 1.0; // t13 expects 1
                }
                if (left == 0.0 && right < 0.0) {
                    handleError();
                }
                //checking if base is negative
                if (left < 0.0) {
                    //rounding the exponent to the nearest whole number
                    double wholeNumber = round(right);

                    //calculating the difference between the exponent and the rounded whole number
                    double difference = fabs(right - wholeNumber);

                    //if the exponent is not a whole number, then it's invalid
                    if (difference > 0.000001) {
                        handleError();
                    }
                }
                result = pow(left, right);
                if (!isfinite(result)) {
                    handleError();
                }
            }
            // Pusing result back to stack
            stack.push(result);
        }
        else {
            // Invalid character
            handleError();
        }
    }
    double finalResult;
    if (!stack.pop(finalResult) || !stack.empty()) {
        handleError();
    }

    cout << finalResult << endl;
    return 0;
}