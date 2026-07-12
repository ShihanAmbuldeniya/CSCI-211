//meme.cpp
//Shihan Embuldeniya
//cembuldeniyaarachchi

#include "meme.h"
#include <iostream>
using namespace std;

Meme::Meme(const string& url, const string& description, const string& category, const double& rating)
    : m_url(url), m_description(description), m_category(category), m_rating(rating) {}

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