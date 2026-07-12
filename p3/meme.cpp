// meme.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include <iostream>
#include <cstdlib>  
#include "meme.h"

using namespace std;

Meme::Meme(string url, string description, string category, double rating) {

    m_url = url;
    m_description = description;
    m_category = category;
    m_rating = rating;
}

bool Meme::category_goes_after(Meme* other) {
    return m_category > other->m_category;
}

bool Meme::rating_goes_after(Meme* other) {
    return m_rating > other->m_rating;
}

string Meme::url() {
    return m_url; 
}

string Meme::category() {
    return m_category;
}

void Meme::print() {
    cout << m_url << endl;
    cout << m_description << endl;
    cout << m_category << endl;
    cout << m_rating << endl;
}

// void Meme::display() {
//     system(("open " + m_url).c_str());
// }

// void Meme::display()
// {
//   string cmd_part_1 = "COMMAND ";
//   string cmd_part_2 = "> /dev/null 2>&1 &";
//   system((cmd_part_1 + m_url + cmd_part_2).c_str());
// }

void Meme::display()
{
    std::string cmd_part_1 = "/usr/bin/open \"";          
    std::string cmd_part_2 = "\" >/dev/null 2>&1 &";      
    system((cmd_part_1 + m_url + cmd_part_2).c_str());
}

