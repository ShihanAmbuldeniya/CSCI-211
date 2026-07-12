// meme.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include "mlist.h"

Mlist::Mlist() { 
    m_head = NULL; 
}

Mlist::~Mlist() {
    // delete every node and its Meme
    Node* ptr = m_head;
    while (ptr != NULL) {
        Node* nxt = ptr->m_next;
        delete ptr->m_value;
        delete ptr;
        ptr = nxt;
    }
    m_head = NULL;
}

bool Mlist::insert(Meme* meme) {
    //checking for duplicate URLs
    for (Node* c = m_head; c != NULL; c = c->m_next) {
        if (c->m_value->url() == meme->url()) {
            return false; 
        }
    }

    //finding where it belongs and sorting it in
    string newCategory = meme->category();
    Node* prev = NULL;
    Node* ptr  = m_head;

    //skiping categories that are smaller than the new one
    while (ptr != NULL && ptr->m_value->category() < newCategory) {
        prev = ptr;
        ptr  = ptr->m_next;
    }
    //then skiping categories equal to the new one
    while (ptr != NULL && ptr->m_value->category() == newCategory) {
        prev = ptr;
        ptr  = ptr->m_next;
    }

    //new node between prev and ptr
    Node* node = new Node(meme, ptr);
        if (prev == NULL){
            m_head = node;     
        } 
        else{
            prev->m_next = node;
        }             
    return true;
}

void Mlist::print() {
    Node* ptr = m_head;
    while (ptr != NULL) {
        ptr->m_value->print();
        ptr = ptr->m_next;
    }
}

int Mlist::length() {
    //counts the number of nodes in the list
    int len = 0;
    for (Node* ptr = m_head; ptr != NULL; ptr = ptr->m_next){
        len++;
    } 
    return len;
}

Meme* Mlist::lookup(string url) {
    //searches for a meme with the given url
    for (Node* ptr = m_head; ptr != NULL; ptr = ptr->m_next) {
        if (ptr->m_value->url() == url){
            return ptr->m_value;
        } 
    }
    return NULL;
}

bool Mlist::display_index(int index) {

    if (index < 0){
        return false;
    }

    Node* ptr = m_head;
    int i = 0;
    while (ptr != NULL && i < index) {
        ptr = ptr->m_next;
        i++;
    }
    if (ptr == NULL){
        return false;
    } 

    ptr->m_value->display();
    return true;
}

bool Mlist::remove(string url) {
    Node* prev = NULL;
    Node* ptr  = m_head;

    while (ptr != NULL) {
        if (ptr->m_value->url() == url) {
            if (prev != NULL){
                prev->m_next = ptr->m_next;
            } 
            else{
                m_head = ptr->m_next;
            }            
            delete ptr->m_value;
            delete ptr;
            return true;
        }
        prev = ptr;
        ptr  = ptr->m_next;
    }
    return false;
}
