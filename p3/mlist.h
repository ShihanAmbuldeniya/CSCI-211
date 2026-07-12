// meme.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#ifndef MLIST_H
#define MLIST_H

#include "meme.h"

using namespace std;

class Mlist
{
    public:
        Mlist();
        ~Mlist();

        bool insert(Meme* meme);  
        void print();    

        int length();
        Meme* lookup(string url);
        bool remove(string url);
        bool display_index(int index);

    private:
        class Node
        {
            public:
                Node(Meme* value, Node* next) {
                    m_value = value;
                    m_next = next;
                }
                Meme* m_value;   
                Node* m_next;    
        };

        Node* m_head;            
};

#endif
