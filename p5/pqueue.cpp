// pqueue.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include "pqueue.h"
#include <climits>
using namespace std;

Pqueue::Pqueue() {
    m_head = NULL;
    m_size = 0;
}

Pqueue::~Pqueue() {
    Node* ptr = m_head; 

    while (ptr != NULL) {
        Node* tmp = ptr;     
        ptr = ptr->m_next;  
        delete tmp;         
    }

    m_head = NULL;       
    m_size = 0;
}

void Pqueue::push(Cust* cust, int priority) {
    Node* newNode = new Node;
    newNode->custPtr = cust;
    newNode->m_priority = priority;
    newNode->m_next = NULL;

    if (m_head == NULL || priority < m_head->m_priority) {
        newNode->m_next = m_head;
        m_head = newNode;
    } else {
        Node* ptr = m_head;
        while (ptr->m_next != NULL && (ptr->m_next->m_priority < priority || ptr->m_next->m_priority == priority)) {
            ptr = ptr->m_next;
        }
        newNode->m_next = ptr->m_next;
        ptr->m_next = newNode;
    }

    m_size += 1;
}

Cust* Pqueue::pop() {
    if (m_head == NULL) {
        return NULL;
    }
    Node* tmp = m_head;          
    m_head = m_head->m_next;     
    Cust* cust = tmp->custPtr;   
    delete tmp;                  
    m_size--;                  
    return cust;                 
}

bool Pqueue::isEmpty() {
    return (m_size == 0);
}

int Pqueue::getSize() {
    return m_size;
}

int Pqueue::getPriorityOfFirstElement() {
    if (m_head == NULL){
        return -1;
    } 
    return m_head->m_priority;
}
