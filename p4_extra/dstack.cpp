// dstack.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include <iostream>
#include "dstack.h"

Dstack::Dstack (){
    m_head = NULL;
} 

Dstack::~Dstack (){
    while (m_head != NULL) {
        Node *tmp = m_head;
        m_head = m_head->m_next;
        delete tmp;
    }
}

void Dstack::push (double value){
    Node *newNode = new Node(value, m_head);
    m_head = newNode;
}

bool Dstack::pop (double &value){
    if (m_head == NULL) {
        return false;
    }
    value = m_head->m_value;

    Node *tmp = m_head;
    m_head = m_head->m_next;
    delete tmp;
    return true;
}


bool Dstack::empty (){
    if (m_head == NULL) {
        return true;
    } else {
        return false;
    }
}