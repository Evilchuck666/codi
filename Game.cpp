/*
 * Game.cpp
 *
 *  Created on: 11 de jun. de 2016
 *      Author: EvilChuck
 */

#include "Game.h"

const int Game::_POINTS[5] = { 2, 5, 10, 15, 25 };

const char *Game::_MOVEMENT_MENU[11] = {
        "DESTINATION COLUMN: ", "CANNOT MOVE THE CARD TO THE COLUMN ",
        "THERE'S NO CARD TO CATCH", "CAN'T PUSH THE CARD",
        "WRITE ORIGIN COLUMN AND ORIGIN ROW: ", "WRITE DESTINATION COLUMN: ",
        "CAN'T MOVE THE CARD", "WRITE ORIGIN COLUMN: ",
        "CANNOT PUSH THE CARD", "WRITE THE STACK: ",
        "THE STACK HAS NO CARD TO RETRIEVE"
};

const char *Game::_STATUS_MENU[9] = {
        "GAME STATUS", "PLAYING GAME", " - M:", " S:[", "]",
        " H:[", "]", "GAME FINISHED", "DISCARDED CARDS: "
};


Game::Game() {

    m_nMoves   = 0;
    m_score = 0;
    m_openCards  = 1;
}

Game::Game(const Deck &deck, const int &open) {

    m_nMoves   = 0;
    m_score = 0;
    m_openCards  = open;

    int cols = _COLS;
    m_board = Board(deck, cols);

    int max = _MAX_CARDS - m_board.nCards();

    for (int i = 0; i < max; i++) {

        Card tmp = deck.getCard(_MAX_CARDS - 1 - i);

        m_hands[0].push(tmp);
    }
}

void Game::openCard() {

    m_lastCards = "";

    if (!m_hands[0].isEmpty()) {

        int nCards = 0;

        while (!m_hands[0].isEmpty() && nCards < m_openCards) {

            Card tmp = m_hands[0].top();
            tmp.turn();

            m_lastCards += tmp.toString();
            m_lastCards += " ";

            m_hands[1].push(tmp);
            m_hands[0].pop();

            nCards++;
        }
    } else if (!m_hands[1].isEmpty()) {

        m_hands[0].inverseCopy(m_hands[1]);
        m_hands[1].release();

        m_score -= _POINTS[(m_openCards == 1 ? 4 : 2)];
    }
    m_nMoves++;
    if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
}

void Game::hand2board() {

    if (m_hands[1].isEmpty())
        cout << _MOVEMENT_MENU[2] << endl;
    else {

        int colD;
        cout << _MOVEMENT_MENU[0];
        cin  >> colD;
        colD--;

        if (colD < 0 || colD > m_board.maxCol())
            cout << _MOVEMENT_MENU[1] << (colD + 1) << endl;
        else {

            Card topCard = m_hands[1].top();

            if (!m_board.pushCard(topCard, colD))
                cout << _MOVEMENT_MENU[1] << (colD + 1) << endl;
            else {
                m_hands[1].pop();
                m_nMoves++;
                m_score += _POINTS[1];

                if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
            }
        }
    }
}

void Game::hand2club() {

    bool doClubbing = false;

    if (m_hands[1].isEmpty())
        cout << _MOVEMENT_MENU[2] << endl;
    else {

        Card desc = m_hands[1].top();
        int top = desc.getClub();

        if (m_clubs[top].isEmpty()) {

            if (desc.getNumber() != 0)
                cout << _MOVEMENT_MENU[3] << endl;
            else
                doClubbing = true;
        } else {

            Card topCard = m_clubs[top].top();

            if (desc > topCard)
                doClubbing = true;
            else
                cout << _MOVEMENT_MENU[3] << endl;
        }

        if (doClubbing) {

            m_clubs[top].push(desc);
            m_hands[1].pop();
            m_nMoves++;
            m_score += _POINTS[2];

            if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
        }
    }
}

void Game::withinBoard() {

    int srcCol, srcRow;
    cout << _MOVEMENT_MENU[4];
    cin >> srcCol >> srcRow;
    srcCol--;
    srcRow--;

    if (srcCol < 0 || srcCol > m_board.maxCol() || srcRow < 0 || srcRow > m_board.getLength(srcCol)) {

            cout << _MOVEMENT_MENU[6] << endl;
    } else {

        bool posValid = m_board.getLength(srcCol) > srcRow;
        bool visible = m_board.getCard(srcCol, srcRow).isVisible();

        if (!visible || !posValid)
            cout << _MOVEMENT_MENU[6] << endl;
        else {

            int dstCol;
            cout << _MOVEMENT_MENU[5];
            cin >> dstCol;
            dstCol--;

            if (dstCol < 0 || dstCol > m_board.maxCol())
                cout << _MOVEMENT_MENU[1] << (dstCol + 1) << endl;
            else {

                bool turned = false;

                if (!m_board.moveCard(srcCol, srcRow, dstCol, turned))
                    cout << _MOVEMENT_MENU[1] << (dstCol + 1) << endl;
                else {

                    m_nMoves++;
                    if (turned) m_score += _POINTS[1];

                    if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
                }
            }
        }
    }
}

void Game::board2club() {

    int srcCol;
    cout << _MOVEMENT_MENU[7];
    cin >> srcCol;
    srcCol--;

    if (srcCol < 0 || srcCol > m_board.maxCol())
        cout << _MOVEMENT_MENU[2] << endl;
    else {

        bool doClubbing = false;
        bool turned = false;

        int srcRow = (m_board.getLength(srcCol) - 1);

        Card club = m_board.getCard(srcCol, srcRow);

        if (m_clubs[club.getClub()].isEmpty()) {

            if (club.getNumber() != 0)
                cout << _MOVEMENT_MENU[8] << endl;
            else
                doClubbing = true;
        } else {

            if (club > m_clubs[club.getClub()].top())
                doClubbing = true;
            else
                cout << _MOVEMENT_MENU[8] << endl;
        }

        if (doClubbing) {

            m_board.popCard(srcCol, turned);
            m_clubs[club.getClub()].push(club);
            m_nMoves++;
            m_score += _POINTS[2];

            if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
        }

        if (turned) m_score += _POINTS[1];
    }
}

void Game::club2board() {

    int club;
    cout << _MOVEMENT_MENU[9];
    cin >> club;
    club--;

    if (club < 0 || club >= _CLUBS)
        cout << _MOVEMENT_MENU[10] << endl;
    else {

        if (m_clubs[club].isEmpty())
            cout << _MOVEMENT_MENU[10] << endl;
        else {

            Card move = m_clubs[club].top();

            int dstCol;
            cout << _MOVEMENT_MENU[0];
            cin >> dstCol;
            dstCol--;

            if (dstCol < 0 || dstCol > m_board.maxCol())
                cout << _MOVEMENT_MENU[1] << (dstCol + 1) << endl;
            else {

                if (!m_board.pushCard(move, dstCol))
                    cout << _MOVEMENT_MENU[1] << (dstCol + 1) << endl;
                else {
                    m_clubs[club].pop();
                    m_nMoves++;
                    m_score -= _POINTS[3];

                    if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
                }
            }
        }
    }
}

bool Game::isFinished() const {
    return m_clubs[0].length() == 13 && m_clubs[1].length() == 13 && m_clubs[2].length() == 13 && m_clubs[3].length() == 13;
}

int Game::getMoves() const {
    return m_nMoves;
}

int Game::getScore() const {
    return m_score;
}

ostream &operator<<(ostream &o, const Game &g) {

    o << endl << Game::_STATUS_MENU[0] << endl;

    o << Game::_STATUS_MENU[8] << g.m_lastCards << endl;

    for (const auto &m_club : g.m_clubs)
        o << m_club;

    o << "   ";

    for (const auto &m_hand : g.m_hands)
        o << m_hand;

    o << endl << g.m_board << endl;

    if (!g.isFinished()) {

        o << Game::_STATUS_MENU[1] << Game::_STATUS_MENU[2] << g.getMoves() << Game::_STATUS_MENU[3];
        o << g.m_clubs[0].length() << Game::_SEP << g.m_clubs[1].length() << Game::_SEP;
        o << g.m_clubs[2].length() << Game::_SEP << g.m_clubs[3].length();
        o << Game::_STATUS_MENU[4] << Game::_STATUS_MENU[5];
        o << g.m_hands[0].length() << Game::_SEP << g.m_hands[1].length();
        o << Game::_STATUS_MENU[6] << " " << g.getScore() << " POINTS" << endl;

    } else
        o << Game::_STATUS_MENU[7] << endl;

    return o;
}
