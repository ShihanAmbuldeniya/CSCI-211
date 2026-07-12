// pqueue.cpp
// Green, Aaron
// asgreen  

#include "pqueue.h"

Pqueue::Pqueue() : m_head(nullptr) {
}

Pqueue::~Pqueue() {
    while (!is_empty()) {
        remove_front();
    }
}

void Pqueue::insert(Cust *cust, int priority) {
    Node *new_node = new Node();
    new_node->cust = cust;
    new_node->priority = priority;
    new_node->next = nullptr;

    // If queue is empty or new priority is lower than head, insert at front
    if (m_head == nullptr || priority < m_head->priority) {
        new_node->next = m_head;
        m_head = new_node;
        return;
    }

    // Find correct position in priority queue
    Node *current = m_head;
    while (current->next != nullptr && current->next->priority <= priority) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

Cust* Pqueue::remove_front() {
    if (is_empty()) {
        return nullptr;
    }

    Node *temp = m_head;
    Cust *cust = temp->cust;
    m_head = m_head->next;
    delete temp;
    return cust;
}

bool Pqueue::is_empty() const {
    return m_head == nullptr;
}

int Pqueue::get_size() const {
    int count = 0;
    Node *current = m_head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

int Pqueue::get_priority_of_first_element() const {
    if (is_empty()) {
        return -1;  // Return -1 if queue is empty
    }
    return m_head->priority;
}
