// pqueue.h
// Embuldeniya, Shihan
// cembuldeniyaarachch

#ifndef PQUEUE_H
#define PQUEUE_H

#include <iostream>
#include "cust.h"
using namespace std;


class Pqueue {
private:
    struct Node {
        Cust* custPtr; // pointer to a customer
        int m_priority; // smaller number = higher priority
        Node* m_next;
    };

    Node* m_head;
    int m_size;

public:
    Pqueue();
    ~Pqueue();

    void push(Cust* cust, int priority); 
    Cust* pop(); 
    bool isEmpty(); 
    int getSize(); 
    int getPriorityOfFirstElement(); 
};

#endif
