//meme.cpp
//Embuldeniya, Shihan
//cembuldeniyaarachchi

#include <iostream>
#include "meme.h"

using namespace std;

//I was curious in learing more about classes and structs in csci111
//and I learnt this inititalizer list style from my csci111 professor
//I use const and & to avoid unnecessary copying of data. he told me that this style is more efficient & safe
Meme::Meme(const string& url, const string& description, const string& category, const double& rating)
    : m_url(url), m_description(description), m_category(category), m_rating(rating) {}

//I could still use this class this way,

// Meme::Meme(const string& url, const string& description, const string& category, const double& rating)
//     m_url = url;
//     m_description = description;
//     m_category = category;
//     m_rating = rating;
// }

bool Meme::category_goes_after(Meme *other) const {
    return m_category > other->m_category;
}

bool Meme::rating_goes_after(Meme *other) const {
    return m_rating > other->m_rating;
}   

void Meme::print() const {
    cout << m_url << endl;
    cout << m_description << endl;
    cout << m_category << endl;
    cout << m_rating << endl;
}