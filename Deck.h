/*
* Deck.h
*
*  Created on: 10 de jun. de 2016
*      Author: EvilChuck
*/

#ifndef DECK_H_
#define DECK_H_

#include "Card.h"

// DESCRIPTION: Class that mixes 52 cards that compounds a deck of cards without jokers

// INVARIANT: m_cardArray is an array of 52 cards

class Deck {

public:

// CONSTRUCTORS

// PRE: --
// POST: --
    Deck();

// PRE: seed > 0
// POST: --
    explicit Deck(const unsigned &seed);

// GETTERS

// PRE: index > 0 && index < _LENGTH
// POST: returns the card at index position of m_cardArray
    Card getCard(const int &index) const;

private:

// CONSTANTS
    static const int _CLUBS = 4;
    static const int _NUMBERS = 13;
    static const int _LENGTH = 52;
    static const int _BOARD_CARDS = 28;
    static const int _HAND_CARDS = 24;


// ATTRIBUTES
    Card m_cardArray[_LENGTH];


// SETTERS

// PRE: --
// POST: m_cardArray is sorted in descendant order
    void initialize();

// PRE: --
// POST: the cards are in a random order
    void fisherYates();


// STATIC CLASS METHODS
    static void plantSeed(const int &seed);

    static unsigned randomizeSeed(unsigned max);

// STATIC CLASS ATTRIBUTE
    static unsigned m_seed;
};
#endif /* DECK_H_ */
