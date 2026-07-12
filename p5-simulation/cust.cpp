// cust.cpp
// Green, Aaron
// asgreen  

#include "cust.h"
#include <cassert>

Cust::Cust(string name, bool is_robber, int arrival_time, int num_items)
    : m_name(name), m_is_robber(is_robber), m_arrival_time(arrival_time), m_num_items(num_items) {
}

void Cust::print_entered(ostream &os, int clock) const {
    assert(clock == m_arrival_time);
    os << clock << ": " << m_name << " entered store" << endl;
}

void Cust::print_done_shopping(ostream &os, int clock) const {
    os << clock << ": " << m_name << " done shopping" << endl;
}

void Cust::print_start_checkout(ostream &os, int clock, int checker_num) const {
    os << clock << ": " << m_name << " started checkout with checker " << checker_num << endl;
}

void Cust::print_done_checkout(ostream &os, int clock, int checker_num, int amount) const {
    string item_word = (m_num_items == 1) ? "item" : "items";
    
    if (m_is_robber) {
        os << clock << ": " << m_name << " stole $" << amount << " and " << m_num_items 
           << " " << item_word << " from checker " << checker_num << endl;
    } else {
        os << clock << ": " << m_name << " paid $" << amount << " for " << m_num_items 
           << " " << item_word << " to checker " << checker_num << endl;
    }
}
