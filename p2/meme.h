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
    Meme(const string& url, const string& description, const string& category, const double& rating);

    bool category_goes_after (Meme* other) const;
    bool rating_goes_after (Meme* other) const;
    
    void print() const;

};

#endif // MEME_H 