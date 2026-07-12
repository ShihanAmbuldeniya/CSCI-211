// pqueue.h
// Green, Aaron
// asgreen  

#ifndef PQUEUE_H
#define PQUEUE_H

#include "cust.h"

struct Node {
    Cust *cust;
    int priority;
    Node *next;
};

class Pqueue {
private:
    Node *m_head;

public:
    Pqueue();
    ~Pqueue();
    
    void insert(Cust *cust, int priority);
    Cust* remove_front();
    bool is_empty() const;
    int get_size() const;
    int get_priority_of_first_element() const;
};

#endif
