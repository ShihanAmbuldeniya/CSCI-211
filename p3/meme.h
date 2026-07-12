//meme.h
//Embuldeniya, Shihan 
//cembuldeniyaarachch

#ifndef MEME_H
#define MEME_H

#include <string>
using namespace std;

class Meme {
private:
    string m_url;
    string m_description;
    string m_category;
    double m_rating;

public:
    Meme(string url, string description, string category, double rating);

    bool category_goes_after(Meme* other);
    bool rating_goes_after(Meme* other);
   
    string url();       
    string category();  

    void print();
    void display();     
};

#endif 