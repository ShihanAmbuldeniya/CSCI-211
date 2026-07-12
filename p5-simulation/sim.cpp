// sim.cpp
// Green, Aaron
// asgreen  

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "pqueue.h"

using namespace std;

/*  flow and logic of the program and specifically checker queue. Had claude draw diagram and formatted it in this comment.
 
  CUSTOMER FLOW THROUGH QUEUES:
  
      ┌─────────────────┐
      │  Input File     │
      └────────┬────────┘
               │ new Cust() in main()
               ↓
      ╔════════════════════════╗
      ║  arrival_queue         ║  Priority = arrival_time
      ║  (sorted by arrival)   ║  
      ║  [Lisa(2)]→[Homer(3)]→[Bart(5)]→NULL
      ╚═══════════┬════════════╝
                  │ At clock == arrival_time
                  │ print_entered()
                  ↓
      ╔════════════════════════╗
      ║  shopping_queue        ║  Priority = done_shopping_time
      ║  (sorted by done time) ║           = arrival_time + (items * 2)
      ║  [Homer(21)]→[Lisa(26)]→[Bart(51)]→NULL
      ╚═══════════┬════════════╝
                  │ At clock == done_shopping_time
                  │ print_done_shopping()
                  ↓
      ╔════════════════════════╗
      ║  checker_queue (FIFO)  ║  Priority = 0 (no priority)
      ║  (first in, first out) ║  
      ║  [Homer]→[Lisa]→[Bart]→NULL
      ╚═══════════┬════════════╝
                  │ When checker available
                  │ print_start_checkout()
                  ↓
         ┌─────────────────┐
         │  Checker Array  │  Customer pointer stored in checker.m_cust
         ├─────────────────┤  
         │ [0] → Homer     │  done_time = clock + items (shopper)
         │ [1] → Lisa      │           or clock + 7 (robber)
         │ [2] → NULL      │  (NULL = idle or on break)
         └─────────────────┘
                  │ At clock == done_time
                  │ print_done_checkout()
                  │ delete cust;  ← Memory freed here
                  ↓
             [COMPLETE]
  
  
  HOW CHECKER QUEUE AND ASSIGNMENT WORKS:
  ========================================
  
  ONE SHARED QUEUE for all checkers (not separate lines):
  
      checker_queue (FIFO - First In, First Out):
      m_head
        ↓
      [Homer] → [Lisa] → [Bart] → [Maggie] → NULL
       ^first                              ^last
  
  
  CHECKER ASSIGNMENT ALGORITHM:
  
  while (checker_queue not empty) {
      
      1. Find LOWEST-NUMBERED AVAILABLE checker:
         
         Checker Array:
         ┌─────────────────────────────────────────┐
         │ [0]: m_cust = NULL                      │ ← Check first
         │      m_break_end_time = 10              │
         │      (clock = 15, so 10 <= 15: AVAILABLE)
         ├─────────────────────────────────────────┤
         │ [1]: m_cust = → [Marge]                 │ ← BUSY (serving customer)
         │      m_done_time = 20                   │
         ├─────────────────────────────────────────┤
         │ [2]: m_cust = NULL                      │ ← ON BREAK
         │      m_break_end_time = 25              │
         │      (clock = 15, so 25 > 15: NOT AVAILABLE)
         └─────────────────────────────────────────┘
         
         RESULT: Checker 0 is selected (lowest available)
      
      
      2. Remove customer from FRONT of checker_queue:
         
         Cust *cust = checker_queue.remove_front();
         // Homer is removed, Lisa is now at front
      
      
      3. Assign customer to selected checker:
         
         checkers[0].m_cust = cust;  // Point to Homer
         
         Calculate done_time:
         - If SHOPPER: done_time = clock + num_items
                       (1 time unit per item)
         - If ROBBER:  done_time = clock + 7
                       (fixed 7 time units)
         
         checkers[0].m_done_time = calculated_done_time;
      
      
      4. Print message:
         
         cust->print_start_checkout(os, clock, 0);
         // "15: Homer started checkout with checker 0"
      
      
      5. Repeat until no available checker OR queue is empty
  }
  
  
  CHECKER AVAILABILITY CONDITIONS:
  
  A checker is AVAILABLE when BOTH are true:
    ✓ checkers[i].m_cust == NULL        (not serving anyone)
    ✓ checkers[i].m_break_end_time <= clock  (break has ended)
  
  A checker is UNAVAILABLE if:
    ✗ m_cust != NULL                     (currently serving)
    ✗ m_break_end_time > clock           (on break after robbery)
  
*/  
 

struct Checker {
    int m_money;
    int m_done_time;  // Time when checker finishes with current customer or break
    Cust *m_cust;     // Current customer being served (NULL if idle)
    int m_break_end_time;  // Time when break ends
};

bool legal_int(string input, int &result) {
    if (input.empty()) return false;
    for (size_t i = 0; i < input.length(); i++) {
        if (!isdigit(input[i])) return false;
    }
    result = stoi(input);
    return true;
}

void run_simulation(Pqueue &arrival_queue, int num_checkers, int break_duration, ostream &os);

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cerr << "Error: invalid number of command line arguments." << endl;
        return 1;
    }

    // check command line arguments
    int num_checkers, break_duration;
    
    if (!legal_int(argv[1], num_checkers)) {
        cerr << "Error: invalid number of checkers specified." << endl;
        return 1;
    }
    
    if (num_checkers < 1) {
        cerr << "Error: invalid number of checkers specified." << endl;
        return 1;
    }

    if (!legal_int(argv[2], break_duration)) {
        cerr << "Error: invalid checker break duration specified." << endl;
        return 1;
    }
    
    if (break_duration < 0) {
        cerr << "Error: invalid checker break duration specified." << endl;
        return 1;
    }

    // Open input file
    ifstream input_file(argv[3]);
    if (!input_file.is_open()) {
        cerr << "Error: could not open input file " << argv[3] << "." << endl;
        return 1;
    }

    // Open output file
    ofstream output_file(argv[4]);
    if (!output_file.is_open()) {
        cerr << "Error: could not open output file " << argv[4] << "." << endl;
        return 1;
    }

    // Read customers from input file
    Pqueue arrival_queue;
    string name, role;
    int arrival_time, num_items;

    while (input_file >> name >> role >> arrival_time >> num_items) {//better approach opposed to using getline()
        Cust *new_cust = new Cust(name, (role == "robber"), arrival_time, num_items);//create node for each customer and attributes
        arrival_queue.insert(new_cust, arrival_time);//insert customers into arrival queue with arrival time as priority
    }

    input_file.close();

    // Run simulation
    run_simulation(arrival_queue, num_checkers, break_duration, output_file);

    output_file.close();
    return 0;
}

void run_simulation(Pqueue &arrival_queue, int num_checkers, int break_duration, ostream &os) {
    // TIMING AND QUEUE SYSTEM:
    // 
    // queue types:
    //   1. arrival_queue  - customers waiting to enter (priority = arrival_time)
    //   2. shopping_queue - customers currently shopping (priority = done_shopping_time)
    //   3. checker_queue  - customers waiting for checkout (FIFO, no priority)
    //
    // TIMING RULES:
    //   Shopping time:  arrival_time + (num_items * 2)
    //                   - Both shoppers and robbers take 2 time per item
    //
    //   Checkout time (shoppers):  start_time + num_items
    //                              - 1 time unit per item
    //
    //   Checkout time (robbers):  start_time + 7
    //                             - Fixed 7 time  regardless of item count
    //
    //   Break duration:  After a robbery, checker is unavailable for break_duration time 
    //
    // EVENT PROCESSING ORDER (per clock tick):
    //   1. Process arrivals (arrival_queue -> shopping_queue)
    //   2. Process done shopping (shopping_queue -> checker_queue)
    //   3. Process checkout completion (update money, print message, handle breaks)
    //   4. Assign customers to available checkers (checker_queue -> checker)
    
    // initialize new checker array ( dynamically allocated based on num_checkers from arg)
    Checker *checkers = new Checker[num_checkers];//dynamic array of checkers, indexed by i
    for (int i = 0; i < num_checkers; i++) {//initialize each checker
        checkers[i].m_money = 250;
        checkers[i].m_cust = NULL;//not serving a customer yet
        checkers[i].m_break_end_time = 0;
    }

    Pqueue shopping_queue;//initialized to NULL based off constructor
    Pqueue checker_queue;//initialized to NULL based off constructor

    int num_customers = arrival_queue.get_size();//number of customers in the arrival queue
    int clock;

    for (clock = 1; num_customers > 0; clock++) {//initialize clock to 1 and increment by 1 until num_customers is 0
        // Process arrivals
        while (!arrival_queue.is_empty() && (arrival_queue.get_priority_of_first_element() == clock)) {//!arrival_queue.is_empty() same as aarival_quese.isempty() == FALSE .  check if priority(time of arrival) == clock
            Cust *cust = arrival_queue.remove_front();
            cust->print_entered(os, clock);
            
            // Calculate done shopping time
            int done_shopping_time = clock + (cust->get_num_items() * 2);
            shopping_queue.insert(cust, done_shopping_time);//creates new node with customer and done_shopping_time as priority
        }

        // Process done shopping
        while (!shopping_queue.is_empty() && shopping_queue.get_priority_of_first_element() == clock) {//check if priority(time of done shopping) == clock
            Cust *cust = shopping_queue.remove_front();
            cust->print_done_shopping(os, clock);
            checker_queue.insert(cust, 0);  // Priority doesn't matter for checker queue
        }

        // Process customers done with checkout
        for (int i = 0; i < num_checkers; i++) {
            if (checkers[i].m_cust != NULL && checkers[i].m_done_time == clock) {
                Cust *cust = checkers[i].m_cust;
                int amount = cust->get_num_items() * 3;  // Each item costs $3
                
                if (cust->is_robber()) {
                    amount = checkers[i].m_money;  // Robber takes all money
                    checkers[i].m_money = 0;
                    checkers[i].m_break_end_time = clock + break_duration;
                } else {
                    checkers[i].m_money += amount;
                }

                cust->print_done_checkout(os, clock, i, amount);
                num_customers--;
                delete cust;
                checkers[i].m_cust = NULL;
            }
        }

        // Assign customers to available checkers
        while (!checker_queue.is_empty()) {
            // Find available checker with lowest index
            int best_checker = -1;
            for (int i = 0; i < num_checkers; i++) {
                if (checkers[i].m_cust == NULL && checkers[i].m_break_end_time <= clock) {
                    best_checker = i;
                    break;
                }
            }

            if (best_checker == -1) break;  // No available checker

            Cust *cust = checker_queue.remove_front();
            checkers[best_checker].m_cust = cust;

            // Calculate done time
            int done_time;
            if (cust->is_robber()) {
                done_time = clock + 7;
            } else {
                done_time = clock + cust->get_num_items();
            }
            checkers[best_checker].m_done_time = done_time;

            cust->print_start_checkout(os, clock, best_checker);
        }
    }

    // Print final results
    for (int i = 0; i < num_checkers; i++) {
        os << "registers[" << i << "] = $" << checkers[i].m_money << endl;
    }
    os << "time = " << clock << endl;

    delete[] checkers;
}
