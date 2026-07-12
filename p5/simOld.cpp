// sim.cpp
// YourLastName, YourFirstName
// ecst_username

#include <iostream>
#include <fstream>
#include <cstdlib>   // atoi
#include "cust.h"
#include "pqueue.h"
using namespace std;

// Simple checker record (no STL)
struct Checker {
    int dollars;        // starts at 250
    int doneTime;     // when current job OR break ends
    Cust* cust;       // customer being served (NULL if none)
};

// Forward
void run_simulation(Pqueue &arrival_q, int num_checkers, int break_duration, ostream &os);

int main(int argc, char* argv[]) {
    // 1) arg count
    if (argc != 5) {
        cerr << "Error: invalid number of command line arguments." << endl;
        return 1;
    }

    // args: [1]=#checkers [2]=break [3]=input [4]=output
    const char* inName  = argv[3];
    const char* outName = argv[4];

    // 2) open input
    ifstream fin(inName);
    if (!fin.is_open()) {
        cerr << "Error: could not open input file " << inName << "." << endl;
        return 1;
    }

    // 3) open output
    ofstream fout(outName);
    if (!fout.is_open()) {
        cerr << "Error: could not open output file " << outName << "." << endl;
        return 1;
    }

    // 4) number of checkers
    int num_checkers = atoi(argv[1]);
    if (num_checkers < 1) {
        cerr << "Error: invalid number of checkers specified." << endl;
        return 1;
    }

    // 5) break duration
    int break_duration = atoi(argv[2]);
    if (break_duration < 0) {
        cerr << "Error: invalid checker break duration specified." << endl;
        return 1;
    }

    // Build arrival queue (priority = arrival time), keep input order on ties
    Pqueue arrival_q;

    string name, role;
    int arrival, items;
    int num_customers = 0;

    // Input format: <name> <shopper/robber> <arrival> <items>
    // Do NOT use getline/eof per spec.
    while (fin >> name >> role >> arrival >> items) {
        bool is_robber = (role == "robber" ? true : false);  // boolean, not the raw string
        Cust* c = new Cust(name, is_robber, arrival, items);
        arrival_q.push(c, arrival);  // use arrival time as priority
        num_customers++;
    }

    // Nothing else reads from fin; run simulation + write to fout
    run_simulation(arrival_q, num_checkers, break_duration, fout);

    return 0;
}

void run_simulation(Pqueue &arrival_q, int num_checkers, int break_duration, ostream &os) {
    // Queues used during sim:
    // - shopping_q: priority = time when done shopping
    // - checker_q: FIFO; we simulate FIFO by using an increasing ticket number as priority
    Pqueue shopping_q;
    Pqueue checker_q;

    // Build checkers at runtime
    Checker* checkers = new Checker[num_checkers];
    for (int i = 0; i < num_checkers; i++) {
        checkers[i].dollars = 250; // all start with $250
        checkers[i].doneTime = 0; // <= clock means available
        checkers[i].cust = NULL;
    }

    // Count total customers to know when to stop
    int total_customers = 0;
    {
        // arrival_q.getSize() is the number custently inside; copy it once
        total_customers = arrival_q.getSize();
    }

    // If input file was empty, we should print registers + time = 1 at the end
    // Loop per spec:
    // for (clock = 1; num_customers > 0; clock++)
    int clock = 1;
    int fifo_ticket = 0; // used to give same-type priority for checker_q (FIFO)

    // Helper lambdas (kept tiny and simple)
    auto checker_available = [&](int idx)->bool {
        return (checkers[idx].cust == NULL && checkers[idx].doneTime <= clock);
    };

    auto find_lowest_available_checker = [&]()->int {
        for (int i = 0; i < num_checkers; i++) {
            if (checker_available(i)) return i;
        }
        return -1;
    };

    // We’ll keep a remaining counter that starts as total_customers and decrements
    // only when a customer COMPLETELY finishes checkout/robbery.
    int remaining = total_customers;

    // Main time loop
    for (; remaining > 0; clock++) {
        // 1) Move arrivals whose arrival_time == clock -> shopping_q
        while (!arrival_q.isEmpty()) {
            Cust* next = arrival_q.peek();
            if (next->getArrivalTime() == clock) {
                // remove
                next = arrival_q.pop();
                // print "entered store"
                next->print_Entered(os, clock);
                // compute done-shopping time: arrival + 2 * items
                int doneShopping = next->getArrivalTime() + 2 * next->getNumItems();
                shopping_q.push(next, doneShopping);
            } else {
                break;
            }
        }

        // 2) Move shoppers done shopping at this time -> checker_q
        while (!shopping_q.isEmpty()) {
            Cust* top = shopping_q.peek();
            // We need to look at the priority; Pqueue doesn't expose it directly,
            // but we only inserted with "doneShopping" == priority.
            // Workaround: since we can't read priority, we can only pop when clock
            // catches up by comparing via try-pop pattern:
            // We'll pop, check if this customer's done time == clock by recomputing:
            // doneShopping = arrival + 2*items. If > clock, we must reinsert.
            // To keep it very simple and avoid extra features in Pqueue, we will
            // only pop when we know it’s ready by checking the earliest element’s
            // recomputed done time and comparing to clock.
            int supposedDone = top->getArrivalTime() + 2 * top->getNumItems();
            if (supposedDone == clock) {
                Cust* c = shopping_q.pop();
                c->print_DoneShopping(os, clock);
                // Place on FIFO checker queue
                checker_q.push(c, fifo_ticket++);
            } else {
                break; // earliest not ready yet, so none are
            }
        }

        // 3) Finish any customers whose checker work ends now (must happen
        //    BEFORE assigning new ones this tick)
        for (int i = 0; i < num_checkers; i++) {
            if (checkers[i].cust != NULL && checkers[i].doneTime == clock) {
                Cust* c = checkers[i].cust;
                if (c->getIsRobber()) {
                    int stolen = checkers[i].dollars;    // robber takes all
                    c->print_FinishCheckout_Robber(os, clock, i, stolen);
                    checkers[i].dollars = 0;
                    // set break end time
                    checkers[i].cust = NULL;
                    checkers[i].doneTime = clock + break_duration;
                } else {
                    int amount = c->getNumItems() * 3; // $3 each
                    checkers[i].dollars += amount;
                    c->print_FinishCheckout_Shopper(os, clock, i, amount);
                    // available immediately (no break for shoppers)
                    checkers[i].cust = NULL;
                    checkers[i].doneTime = clock; // <= clock -> available
                }
                // this customer is fully done with the store
                delete c;
                remaining--;
            }
        }

        // 4) While there’s an available checker and someone waiting in checker_q,
        //    assign and start their checkout now (start time = clock)
        while (!checker_q.isEmpty()) {
            int idx = find_lowest_available_checker();
            if (idx == -1) break;

            Cust* c = checker_q.pop();
            checkers[idx].cust = c;

            int duration;
            if (c->getIsRobber()) duration = 7;
            else                  duration = c->getNumItems(); // 1 per item

            checkers[idx].doneTime = clock + duration;
            c->print_StartCheckout(os, clock, idx);
        }
        // loop continues; clock++ at top for next tick
    }

    // After loop: print all registers and the final time (clock is one past last finish)
    for (int i = 0; i < num_checkers; i++) {
        os << "registers[" << i << "] = $" << checkers[i].dollars << endl;
    }
    os << "time = " << clock << endl;

    delete [] checkers;
}
