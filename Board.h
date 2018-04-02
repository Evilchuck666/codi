/*
* Board.h
*
*  Created on: 10 de jun. de 2016
*      Author: EvilChuck
*/

#ifndef BOARD_H_
#define BOARD_H_

#include "Deck.h"
#include "Card.h"
#include <ostream>

// DESCRIPTION: Manages and prints the layout of cards over the board,
//              and checks if the movements are legal, otherwise
//              it will give a warning and abort the movement.

// INVARIANT: m_board must agree Card INVARIANT and integer attributes
//            must be positives.

class Board {

public:

// INITIALIZER

// PRE: --
// POST: Fills dynamic matrix m_board from cards of deck
    void fillMatrix(const Deck &deck);


// CONSTRUCTORS

// PRE: --
// POST: --
    Board();

// PRE: --
// POST: cols > 0
    Board(const Deck &deck, const int &cols);

// PRE: --
// POST: copies b to this
    Board(const Board &b);


// GETTERS

// PRE: --
// POST: returns the total of cards used in creating the board
    int nCards() const;

// PRE: --
// POST: returns the number of columns the board uses
    int maxCol() const;

// PRE: srcCol >= 0 && srcCol <= maxCol()
// PRE: srcRow >= 0 && srcRow <= m_length[srcCol] - 1
// POST: returns the card at [srcCol,srcRow]
    Card getCard(const int &srcCol, const int &srcRow) const;

// PRE: col >= 0 && col <= maxCol()
// POST: returns the number of cards in column col
    int getLength(const int &col) const;


// SETTERS

// PRE: col >= 0 && col <= maxCol()
// POST: true if can add the card, false otherwise
    bool pushCard(const Card &c, const int &col);

// PRE: col >= 0 && col <= maxCol(), turned must be boolean
// POST: true if can remove the card from col, false otherwise
    bool popCard(const int &col, bool &turned);

// PRE: srcCol and dstCol must be between 0 and maxCol()
// PRE: srcRow must be between 0 and m_length[srcCol] - 1,
// PRE: turned must be boolean
// POST: true if can move the card from [srcCol,srcRow] to dstCol
    bool moveCard(const int &srcCol, const int &srcRow, const int &dstCol, bool &turned);


// OPERATORS

// PRE: --
// POST: sets b attributes to this
    Board &operator=(const Board &b);


// FLUX OPERATORS

// PRE: --
// POST: prints b layout
    friend ostream &operator<<(ostream &o, const Board &b);

private:

// CONSTANTS
    static const int _DEFAULT_COLUMNS = 7;
    static const int _MAX_ROWS = 19;
    static const int _CLUB_CARDS = 13;


// ATTRIBUTES
    Card **m_board;

    int *m_length;
    int *m_maxLength;

    int m_cols;

    int m_nCards;


// PRIVATE METHODS

// PRE: cols > 0
// POST: creates board structure
    void initialize(const int &cols);

// PRE: --
// POST: sets initial and maximum length of each column
    void createArray();

// PRE: --
// POST: creates m_board
    void createMatrix();

// PRE: --
// POST: turn the last card of each column
    void turnCards();

// PRE: --
// POST: makes a copy of b
    void clone(const Board &b);

// PRE: srcCol and dstCol must be between 0 and maxCol()
// PRE: srcRow must be between 0 and m_length[srcCol] - 1,
// PRE: turned must be boolean
// POST: true if can move the cards from [srcCol,srcRow] to dstCol
    void move(const int &srcCol, const int &srcRow, const int &dstCol, bool &turned);

// PRE: --
// POST: returns the longest row
    int longestRow() const;

};

#endif /* BOARD_H_ */
