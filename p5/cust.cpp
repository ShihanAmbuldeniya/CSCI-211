// cust.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include <iostream>
#include <cassert>
#include "cust.h"

// Constructor
Cust::Cust (string name, bool is_robber, int arrival_time, int num_items){
    m_name = name;
    m_is_robber = is_robber;
    m_arrival_time = arrival_time;
    m_num_items = num_items;
}

// Getter functions
string Cust::getName() { 
    return m_name; 
}

bool Cust::getIsRobber() {
    return m_is_robber; 
}

int Cust::getArrivalTime() { 
    return m_arrival_time; 
}

int Cust::getNumItems() { 
    return m_num_items; 
}

int Cust::getCheckoutDuration()
{
    if (m_is_robber){
        return 7; // robbers always 7
    } 
    else {
        return m_num_items; //shoppers: 1 per item
    }
}

//print functions
void Cust::print_Entered(ostream &os, int clock){
    // assert(clock == m_arrival_time); 
    os << clock << ": " << m_name << " entered store" << endl;
}

void Cust::print_DoneShopping(ostream &os, int clock){
    os << clock << ": " << m_name << " done shopping" << endl;
}

void Cust::print_StartCheckout(ostream &os, int clock, int checkerIndex){
    os << clock << ": " << m_name << " started checkout with checker " << checkerIndex << endl;
}

void Cust::print_FinishCheckout_Shopper(ostream &os, int clock, int checkerIndex, int amount){
    os << clock << ": " << m_name << " paid $" << amount << " for " << m_num_items;

    if (m_num_items == 1)
        os << " item";
    else
        os << " items";

    os << " to checker " << checkerIndex << endl;
}

void Cust::print_FinishCheckout_Robber(ostream &os, int clock, int checkerIndex, int stolenAmount){
    os << clock << ": " << m_name << " stole $" << stolenAmount << " and " << m_num_items;

    if (m_num_items == 1)
        os << " item";
    else
        os << " items";

    os << " from checker " << checkerIndex << endl;
}


