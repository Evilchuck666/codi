/*
* Game.h
*
*  Created on: 11 de jun. de 2016
*      Author: EvilChuck
*/

#ifndef GAME_H_
#define GAME_H_

#include "Deck.h"
#include "Stack.h"
#include "Board.h"
#include <iostream>
#include <string>

using namespace std;


// DESCRIPTION:	Game class manages the layout as well the stacks of each
//              club and stacks of each hand.
//              When doing a move, the class can ask to the user.
//              If the user tries a wrong and/or illegal move, it'll return
//              a warning and won't commit the action.

// INVARIANT:	Every object must agree its INVARIANT as well as
//              m_nMoves and m_openCards must be positives integers.

class Game {

public:

// CONSTRUCTORS

// PRE: --
// POST: --
    Game();

// PRE: --
// POST: --
    Game(const Deck &deck, const int &open);


// SETTERS (GAME ACTIONS)

// PRE: --
// POST: open cards
    void openCard();

// PRE: --
// POST: moves a card from hand to the board
    void hand2board();

// PRE: --
// POST: moves a card from hand to its club stack
    void hand2club();

// PRE: --
// POST: moves one or more cards within the table
    void withinBoard();

// PRE: --
// POST: moves a card from the board to its club stack
    void board2club();

// PRE: --
// POST: moves a card from its club stack back to the table
    void club2board();


// GETTERS

// PRE: --
// POST: returns if the game is finished
    bool isFinished() const;

// PRE: --
// POST: returns the numbers of moves already made
    int getMoves() const;

// PRE: --
// POST: returns the score
    int getScore() const;


// FLUX OPERATORS

// PRE: --
// POST: shows the discarded cards, the stacks, the table
//       and game statistics
    friend ostream &operator<<(ostream &o, const Game &g);

private:

// CONSTANTS
    static const int _MAX_CARDS = 52;

    static const int _COLS = 7;
    static const int _CLUBS = 4;
    static const int _HANDS = 2;

    static const int _POINTS[5];

    static const char _SEP = ',';
    static const string _MOVEMENT_MENU[11];
    static const string _STATUS_MENU[9];


// ATTRIBUTES
    Stack m_hands[_HANDS];
    Stack m_clubs[_CLUBS];

    Board m_board;

    int m_nMoves;
    int m_score;
    int m_openCards;

    string m_lastCards;
};

#endif /* GAME_H_ */
