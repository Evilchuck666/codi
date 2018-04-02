/*
* Card.h
*
*  Created on: 10 de jun. de 2016
*      Author: EvilChuck
*/

#ifndef CARD_H_
#define CARD_H_

#include <ostream>
#include <string>

using namespace std;

// DESCRIPTION: Class that saves the club and number of the card
//              and if it's visible.

// INVARIANT: m_club >= 0 && m_club <= 3
// INVARIANT: m_number >= 0 && m_number <= 12
// INVARIANT: m_visible must be boolean

class Card {

public:

// CONSTRUCTORS

// PRE: --
// POST: --
    Card();

// PRE: p and n must be positive integers
// POST: --
    Card(const int &p, const int &n);


// PRE: --
// POST: copies c attributes to this
    Card(const Card &c);


// GETTERS

// PRE: --
// POST: returns m_club
    int getClub() const;

// PRE: --
// POST: returns m_number
    int getNumber() const;

// PRE: --
// POST: returns m_visible
    bool isVisible() const;

// PRE: --
// POST: returns m_club and m_number in a string
    string toString() const;


// SETTERS

// PRE: --
// POST: swaps m_visible boolean
    void turn();


// OPERATORS

// PRE: --
// POST: compares if this is greater than c
    bool operator>(const Card &c) const;

// PRE: --
// POST: compares if this is lower than c
    bool operator<(const Card &c) const;

// PRE: --
// POST: sets attributes from c to this
    Card &operator=(const Card &c);


private:

// CONSTANTS
    static const int _N_CLUBS = 4;
    static const int _N_NUMBERS = 13;
    static const int _CH_COL = 3;
    static const char _CLUBS[_N_CLUBS];
    static const char _NUMBERS[_N_NUMBERS];


// ATTRIBUTES
    int m_club;
    int m_number;
    bool m_visible;
    bool m_colour;

// PRIVATE METHODS
    string constructCard() const;
};

#endif /* CARD_H_ */
