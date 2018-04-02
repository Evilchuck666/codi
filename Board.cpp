/*
 * Board.cpp
 *
 *  Created on: 10 de jun. de 2016
 *      Author: EvilChuck
 */

#include "Board.h"
#include "Stack.h"

void Board::initialize(const int &cols) {

    m_cols = cols;
    m_nCards = 0;

    m_length = new int[m_cols];
    m_maxLength = new int[m_cols];

    createArray();
    createMatrix();
}

void Board::createArray() {

    for (int i = 0; i < m_cols; i++) {

        m_length[i] = (i + 1);
        m_maxLength[i] = (i + _CLUB_CARDS);
    }
}

void Board::createMatrix() {

    m_board = new Card*[m_cols];

    for (int i = 0; i < m_cols; i++)
        m_board[i] = new Card[m_maxLength[i]];
}

void Board::fillMatrix(const Deck &deck) {

    for (int i = 0; i < m_cols; i++) {

        int max = m_length[(m_cols - 1) - i];

        for (int j = 0; j < max; j++) {

            m_board[j + i][i] = deck.getCard(m_nCards);
            m_nCards++;
        }
    }
}

void Board::turnCards() {

    for (int i = 0; i < m_cols; i++)
        m_board[i][m_length[i] - 1].turn();
}

void Board::clone(const Board &b) {

    initialize(b.m_cols);

    for (int i = 0; i < m_cols; i++) {

        m_length[i] = b.m_length[i];
        m_maxLength[i] = b.m_maxLength[i];

        for (int j = 0; j < m_length[i]; j++)
            m_board[i][j] = b.getCard(i, j);
    }
    m_nCards = b.m_nCards;
}


Board::Board() {

    int cols = _DEFAULT_COLUMNS;
    initialize(cols);
}

Board::Board(const Deck &deck, const int &cols) {

    initialize(cols);
    fillMatrix(deck);
    turnCards();
}

Board::Board(const Board &b) {

    initialize(b.m_cols);
    clone(b);
}


int Board::nCards() const {
    return m_nCards;
}

int Board::maxCol() const {
    return (m_cols - 1);
}

Card Board::getCard(const int &srcCol, const int &srcRow) const {
    return m_board[srcCol][srcRow];
}

int Board::getLength(const int &col) const {
    return m_length[col];
}

bool Board::pushCard(const Card &c, const int &col) {

    bool continuePush = false;
    int index = 0;

    if (m_length[col] < m_maxLength[col] && m_length[col] > 0) {

        Card previousCard = m_board[col][m_length[col] - 1];

        if (c < previousCard) {

            continuePush = true;
            index = m_length[col];
        }
    } else {

        if (m_length[col] == 0 && c.getNumber() == 12)
            continuePush = true;
    }

    if (continuePush) {

        m_board[col][index] = c;
        m_length[col]++;
    }
    return continuePush;
}

bool Board::popCard(const int &col, bool &turned) {

    if (m_length[col] == 0) return false;

    m_length[col]--;

    Card card = m_board[col][m_length[col] - 1];

    if (!card.isVisible()) {

        m_board[col][m_length[col] - 1].turn();
        turned = true;
    }
    return true;
}

void Board::move(const int &srcCol, const int &srcRow, const int &dstCol, bool &turned) {

    Stack tmp;

    for (int i = (m_length[srcCol] - 1); i >= srcRow; i--) {

        tmp.push(m_board[srcCol][i]);
        popCard(srcCol, turned);
    }

    int newLength = m_length[dstCol] + tmp.length();

    for (int i = m_length[dstCol]; i < newLength; i++) {

        pushCard(tmp.top(), dstCol);
        tmp.pop();
    }
}

bool Board::moveCard(const int &srcCol, const int &srcRow, const int &dstCol, bool &turned) {

    if (m_length[dstCol] == 0) {

        if (m_board[srcCol][srcRow].getNumber() != 12)
            return false;
        else
            move(srcCol, srcRow, dstCol, turned);
    } else {

        Card greater = m_board[dstCol][m_length[dstCol] - 1];
        Card lower = m_board[srcCol][srcRow];

        if (!(lower < greater))
            return false;
        else
            move(srcCol, srcRow, dstCol, turned);
    }
    return true;
}

Board &Board::operator =(const Board &b) {

    createArray();
    createMatrix();
    clone(b);

    return *this;
}

ostream &operator<<(ostream &o, const Board &b) {

    for (int c = 1; c <= b.m_cols; c++)
        o << "c" << c << " ";
    o << endl;

    int rows = b.longestRow();

    for (int f = 0; f < rows; f++) {

        for (int j = 0; j < b.m_cols; j++) {

            int tab = b.m_length[j];

            if (f < tab)
                o << b.m_board[j][f].toString() << " ";
            else
                o << "   ";
        }
        o << "f" << (f + 1) << endl;
    }
    return o;
}

int Board::longestRow() const {

    int max = 0;

    for (int i = 0; i < m_cols; i++) {

        if (m_length[i] > max)
            max = m_length[i];
    }
    return max;
}
