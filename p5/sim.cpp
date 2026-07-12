// sim.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cctype>  
#include "cust.h"
#include "pqueue.h"

using namespace std;

const int ITEM_PRICE = 3; // $3 per item

struct Checker {
    int money; // money in the register
    int done_time; // time when current service or break ends 
    Cust* currentCust; // currently served customer 
};


void run_simulation(Pqueue &arrival_queue, int num_checkers, int break_duration, ostream &os);

bool legal_int(const string &input) {
    if (input.empty()){
        return false;
    } 
    for (size_t i = 0; i < input.length(); i++) {
        if (!isdigit(input[i])){
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    // Command line: num_checkers, break_duration, input file, output file
    if (argc != 5) {
        cerr << "Error: invalid number of command line arguments." << endl;
        return 1;
    }

    string num_checkers_str = argv[1];
    string break_duration_str = argv[2];
    string input_filename = argv[3];
    string output_filename = argv[4];

    ifstream fin(input_filename);
    if (!fin) {
        cerr << "Error: could not open input file <" << input_filename << ">." << endl;
        return 1;
    }

    ofstream fout(output_filename);
    if (!fout) {
        cerr << "Error: could not open output file <" << output_filename << ">." << endl;
        return 1;
    }

    if (!legal_int(num_checkers_str)) {
        cerr << "Error: invalid number of checkers specified." << endl;
        return 1;
    }
    if (!legal_int(break_duration_str)) {
        cerr << "Error: invalid checker break duration specified." << endl;
        return 1;
    }

    int num_checkers = stoi(num_checkers_str);
    int break_duration = stoi(break_duration_str);

    if (num_checkers < 1) {
        cerr << "Error: invalid number of checkers specified." << endl;
        return 1;
    }
    if (break_duration < 0) {
        cerr << "Error: invalid checker break duration specified." << endl;
        return 1;
    }

    // Build arrival queue from input
    Pqueue arrival_q;
    string name, role;
    int arrival_time, num_items;

    while (fin >> name >> role >> arrival_time >> num_items) {
        bool is_robber = false;  // false = shopper, true = robber
        if (role == "robber") {
            is_robber = true;
        }
        Cust* customer = new Cust(name, is_robber, arrival_time, num_items);
        arrival_q.push(customer, arrival_time);
    }

    run_simulation(arrival_q, num_checkers, break_duration, fout);

    return 0;
}

void run_simulation(Pqueue &arrival_queue, int num_checkers, int break_duration, ostream &os) {
    // Create and initialize checkers
    Checker *checkers = new Checker[num_checkers];
    int i;
    for (i = 0; i < num_checkers; i++) {
        checkers[i].money = 250;
        checkers[i].done_time = 0;
        checkers[i].currentCust = NULL;
    }

    // Other queues used in simulation
    Pqueue shopping_queue; 
    Pqueue checker_queue; 

    // Count of customers total
    int num_customers = arrival_queue.getSize();

    int clock;
    for (clock = 1; num_customers > 0; clock++) {

        // 1) 
        while (!arrival_queue.isEmpty() && arrival_queue.getPriorityOfFirstElement() == clock) {
            Cust* cust = arrival_queue.pop();
            cust->print_Entered(os, clock);

            int done_shop_time = clock + (cust->getNumItems() * 2);
            shopping_queue.push(cust, done_shop_time);
        }

        // 2) 
        while (!shopping_queue.isEmpty() && shopping_queue.getPriorityOfFirstElement() == clock) {
            Cust* cust = shopping_queue.pop();
            cust->print_DoneShopping(os, clock);
            checker_queue.push(cust, 0);
        }

        // 3) 
        for (i = 0; i < num_checkers; i++) {
            Cust* cust = checkers[i].currentCust;
            if (cust != NULL && checkers[i].done_time == clock) {
                // Service finished at this time
                if (cust->getIsRobber()) {
                    int stolen = checkers[i].money;
                    cust->print_FinishCheckout_Robber(os, clock, i, stolen);
                    checkers[i].money = 0;
                    // set break end time
                    checkers[i].done_time = clock + break_duration;
                } else {
                    int amount = cust->getNumItems() * ITEM_PRICE;
                    cust->print_FinishCheckout_Shopper(os, clock, i, amount);
                    checkers[i].money += amount;
                    // immediately available
                    checkers[i].done_time = clock;
                }

                // customer leaves store
                delete cust;
                checkers[i].currentCust = NULL;
                num_customers --;
            }
        }

        // 4) 
        bool assigned = true;
        while (assigned && !checker_queue.isEmpty()) {
            assigned = false;
            // find lowest index available checker
            int checkerIndex = -1;
            for (i = 0; i < num_checkers; i++) {
                if (checkers[i].currentCust == NULL && checkers[i].done_time <= clock) {
                    checkerIndex = i;
                    break;
                }
            }
            if (checkerIndex != -1) {
                Cust* nextCustomer = checker_queue.pop();
                checkers[checkerIndex].currentCust = nextCustomer;
                nextCustomer->print_StartCheckout(os, clock, checkerIndex);

                int checkoutTime = nextCustomer->getCheckoutDuration();
                checkers[checkerIndex].done_time = clock + checkoutTime;

                assigned = true;
            }
        }
    }

    // After simulation, print registers and current time
    for (i = 0; i < num_checkers; i++) {
        os << "registers[" << i << "] = $" << checkers[i].money << endl;
    }
    os << "time = " << clock << endl;

    delete [] checkers;
}
