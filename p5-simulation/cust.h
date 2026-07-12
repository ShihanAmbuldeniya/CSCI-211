// cust.h
// Green, Aaron
// asgreen

#ifndef CUST_H
#define CUST_H

#include <iostream>
#include <string>

using namespace std;

class Cust {
private:
    string m_name;
    bool m_is_robber;  // true if robber, false if shopper
    int m_arrival_time;
    int m_num_items;

public:
    Cust(string name, bool is_robber, int arrival_time, int num_items);
    
    // Getters
    string get_name() const { return m_name; }
    bool is_robber() const { return m_is_robber; }
    int get_arrival_time() const { return m_arrival_time; }
    int get_num_items() const { return m_num_items; }
    
    // Print functions
    void print_entered(ostream &os, int clock) const;
    void print_done_shopping(ostream &os, int clock) const;
    void print_start_checkout(ostream &os, int clock, int checker_num) const;
    void print_done_checkout(ostream &os, int clock, int checker_num, int amount) const;
};

#endif
