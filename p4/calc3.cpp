// calc.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include "dstack.h"

using namespace std;

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
                cerr << "Error: Invalid expression.\n";
                exit(1);
            }
            stack.push(number);
            continue;
        }
        else if (nextChar == '-' || nextChar == '+') {
            // Could be a signed number or an operator
            // Looking ahead to see what follows
            cin.get(); //get the sign
            int nextNext = cin.peek();
            
            if (isdigit(nextNext) || nextNext == '.') {
                // It's a signed number like -5 or +3.14
                cin.putback(nextChar); // put back the sign
                if (!(cin >> number)) {
                    cerr << "Error: Invalid expression.\n";
                    exit(1);
                }
                stack.push(number);
                continue;
            }
            else {
                // It's an operator, not a signed number
                operation = nextChar;
            }
        }
        else {
            // It's an operator
            cin >> operation;
        }

        // Operations
        if (operation == '+' || operation == '-' || operation == '*' || operation == '/' || operation == '^') {
            // Pop two numbers from stack
            if (!stack.pop(right)) {
                cerr << "Error: Invalid expression.\n";
                exit(1);
            }
            if (!stack.pop(left)) {
                cerr << "Error: Invalid expression.\n";
                exit(1);
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
                    cerr << "Error: Invalid expression.\n";
                    exit(1);
                }
                result = left / right;
            } 
            else if (operation == '^') {
                if (left == 0.0 && right == 0.0) {
                    cerr << "Error: Invalid expression.\n";
                    exit(1);
                }
                if (left == 0.0 && right < 0.0) {
                    cerr << "Error: Invalid expression.\n";
                    exit(1);
                }
                //checking if base is negative
                if (left < 0.0) {
                    //rounding the exponent to the nearest whole number
                    double wholeNumber = round(right);

                    //calculating the difference between the exponent and the rounded whole number
                    double difference = fabs(right - wholeNumber);

                    //if the exponent is not a whole number, then it's invalid
                    if (difference > 0.000001) {
                        cerr << "Error: Invalid expression.\n";
                        exit(1);
                    }
                }
                result = pow(left, right);
                if (!isfinite(result)) {
                    cerr << "Error: Invalid expression.\n";
                    exit(1);
                }
            }
            // Pushing result back to stack
            stack.push(result);
        }
        else {
            // Invalid character
            cerr << "Error: Invalid expression.\n";
            exit(1);
        }
    }
    
    double finalResult;
    if (!stack.pop(finalResult) || !stack.empty()) {
        cerr << "Error: Invalid expression.\n";
        exit(1);
    }

    cout << finalResult << endl;
    return 0;
}