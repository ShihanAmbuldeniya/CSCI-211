// cust.h
// Embuldeniya, Shihan
// cembuldeniyaarachch

#ifndef CUST_H
#define CUST_H

#include <iostream>
#include <string>

using namespace std;

class Cust{
    private:
        string m_name;
        bool m_is_robber; //true == robber, false == shopper
        int m_arrival_time;
        int m_num_items;
        int m_doneShoppingTime;

    public:
        Cust (string name, bool is_robber, int arrival_time, int num_items);

        //getters
        string getName();
        bool getIsRobber();
        int getArrivalTime();
        int getNumItems();

        int getCheckoutDuration();

        //print functions
        void print_Entered(ostream &os, int clock);
        void print_DoneShopping(ostream &os, int clock);
        void print_StartCheckout(ostream &os, int clock, int checkerIndex);
        void print_FinishCheckout_Shopper(ostream &os, int clock, int checkerIndex, int amount);
        void print_FinishCheckout_Robber(ostream &os, int clock, int checkerIndex , int stolenAmount);

};

#endif