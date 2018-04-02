//============================================================================
// Name        : main.cpp
// Author      : EvilChuck
// Version     : v0.666
// Copyright   : SatanicWorks
// Description : Solitario en versión consola
//============================================================================

#include <iostream>
#include "Deck.h"
#include "Game.h"

using namespace std;

// PRE: --
// POST: seed > 0
void readSteps(int &seed) {

    do {
        cout << "WRITE A POSITIVE INTEGER: ";
        cin >> seed;

    } while (seed <= 0);
}

// PRE: --
// POST: open == 1 || open == 2
void openCards(int &open) {

    do {
        cout << "HOW MANY CARDS DO YOU WANT TO OPEN?" << endl;
        cout << "1.- ONE BY ONE" << endl;
        cout << "2.- THREE BY THREE" << endl;
        cin >> open;

    } while (!(open > 0 && open < 3));

    if (open == 2) open = 3;
}

// PRE: --
// POST: --
void menu(const int &open) {

    cout << "MENU" << endl;

    if (open == 1)
        cout << "1. OPEN A CARD (OR BEGIN AGAIN)" << endl;
    else
        cout << "1. OPEN THREE CARDS (OR BEGIN AGAIN)" << endl;

    cout << "2. MOVE A CARD (HAND->TABLE)" << endl;
    cout << "3. MOVE A CARD (HAND->STACK)" << endl;
    cout << "4. MOVE A CARD (WITHIN TABLE)" << endl;
    cout << "5. MOVE A CARD (TABLE->STACK)" << endl;
    cout << "6. RESTORE A CARD (STACK->TABLE)" << endl;
    cout << "9. SHOW MENU" << endl;
    cout << "0. EXIT GAME" << endl;
}


// DESCRIPTION: Reads a positive plantSeed, immediately asks if you want to open
//              the cards in one by one or three by three.
//              Once written those values, game begins, showing first the status
//              of the board and showing the menu.
//              If you write an undefined option it will give a warning message
//              without doing any action at all, if we put a legal action instead
//              the game will try to make that action following the rules
//              and will show another warning if that action cannot be made.
//              The game finishes when all cards are set to its respective club,
//              or when the player abandones the game.
//              This game is based on the basic rules of the most popular solitaire
//              or also known as Klondike.

int main() {

    int seed;
    int open;

    readSteps(seed);
    openCards(open);

    Deck mainDeck(seed);

    Game mainGame(mainDeck, open);

    cout << mainGame << endl;
    menu(open);

    int option;
    cout << "OPTION: ";
    cin >> option;

    while (option != 0 && !mainGame.isFinished()) {

        if (option == 1) mainGame.openCard();
        else if (option == 2) mainGame.hand2board();
        else if (option == 3) mainGame.hand2club();
        else if (option == 4) mainGame.withinBoard();
        else if (option == 5) mainGame.board2club();
        else if (option == 6) mainGame.club2board();
        else if (option == 9) menu(open);
        else {

            cout << "UNDEFINED OPTION " << option << endl;
            menu(open);
        }

        if (option != 9) cout << mainGame << endl;

        if (!mainGame.isFinished()) {

            cout << "OPTION: ";
            cin >> option;
        }
    }

    if (!mainGame.isFinished())
        cout << "ABANDONED GAME" << endl;
    else {
        cout << "YOU WON THE GAME WITH " << mainGame.getMoves() << " MOVES";
        cout << " AND WITH A SCORE OF " << mainGame.getScore() << " POINTS" << endl;
    }

    return 0;
}
