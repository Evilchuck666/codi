/*
 * Game.cpp
 *
 *  Created on: 11 de jun. de 2016
 *      Author: EvilChuck
 */

#include "Game.h"

const int Game::_POINTS[5] = { 2, 5, 10, 15, 25 };

const string Game::_MOVEMENT_MENU[11] = {
		"DESTINATION COLUMN: ", "CANNOT MOVE THE CARD TO THE COLUMN ",
		"THERE'S NO CARD TO CATCH", "CAN'T PUSH THE CARD",
		"WRITE ORIGIN COLUMN AND ORIGIN ROW: ", "WRITE DESTINATION COLUMN: ",
		"CAN'T MOVE THE CARD", "WRITE ORIGIN COLUMN: ",
		"CANNOT PUSH THE CARD", "WRITE THE STACK: ",
		"THE STACK HAS NO CARD TO RETRIEVE"
};

const string Game::_STATUS_MENU[9] = {
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

		int nCartas = 0;

		while (!m_hands[0].isEmpty() && nCartas < m_openCards) {

			Card tmp = m_hands[0].top();
			tmp.turn();

			m_lastCards += tmp.toString();
			m_lastCards += " ";

			m_hands[1].push(tmp);
			m_hands[0].pop();

			nCartas++;
		}
		m_nMoves++;
		if (m_nMoves % 10 == 0) m_score -= _POINTS[0];

	} else {

		if (!m_hands[1].isEmpty()) {

			m_hands[0].inverseCopy(m_hands[1]);
			m_hands[1].release();
			m_nMoves++;

			if (m_openCards == 1) m_score -= _POINTS[4];
			else                  m_score -= _POINTS[2];

			if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
		}
	}
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

			Card dest = m_hands[1].top();

			if (!m_board.pushCard(dest, colD))
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

	if (m_hands[1].isEmpty())
		cout << _MOVEMENT_MENU[2] << endl;
	else {

		Card desc = m_hands[1].top();
		int cima = desc.getClub();

		if (m_clubs[cima].isEmpty()) {

			if (desc.getNumber() != 0)
				cout << _MOVEMENT_MENU[3] << endl;
			else {

				m_clubs[cima].push(desc);
				m_hands[1].pop();
				m_nMoves++;
				m_score += _POINTS[2];

				if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
			}
		} else {

			Card cimPalo = m_clubs[cima].top();

			if (desc > cimPalo) {

				m_clubs[cima].push(desc);
				m_hands[1].pop();
				m_nMoves++;
				m_score += _POINTS[2];

				if (m_nMoves % 10 == 0) m_score -= _POINTS[0];

			} else
				cout << _MOVEMENT_MENU[3] << endl;
		}
	}
}

void Game::withinBoard() {

	int colO, filaO;
	cout << _MOVEMENT_MENU[4];
	cin  >> colO >> filaO;
	colO--; filaO--;

	if (colO  < 0 || colO  > m_board.maxCol() ||
		filaO < 0 || filaO > m_board.getLength(colO)) {

			cout << _MOVEMENT_MENU[6] << endl;

	} else {

		bool posValid = m_board.getLength(colO) > filaO;
		bool visible  = m_board.getCard(colO, filaO).isVisible();

		if (!visible || !posValid)
			cout << _MOVEMENT_MENU[6] << endl;
		else {

			int colD;
			cout << _MOVEMENT_MENU[5];
			cin  >> colD;
			colD--;

			if (colD < 0 || colD > m_board.maxCol())
				cout << _MOVEMENT_MENU[1] << (colD + 1) << endl;
			else {

				bool volteado = false;

				if (!m_board.moveCard(colO, filaO, colD, volteado))
					cout << _MOVEMENT_MENU[1] << (colD + 1) << endl;
				else {

					m_nMoves++;
					if (volteado) m_score += _POINTS[1];

					if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
				}
			}
		}
	}
}

void Game::board2club() {

	int colO;
	cout << _MOVEMENT_MENU[7];
	cin  >> colO;
	colO--;

	if (colO < 0 || colO > m_board.maxCol())
		cout << _MOVEMENT_MENU[2] << endl;
	else {

		bool volteado = false;

		int filaO = (m_board.getLength(colO) - 1);

		Card palo = m_board.getCard(colO, filaO);

		if (m_clubs[palo.getClub()].isEmpty()) {

			if (palo.getNumber() != 0)
				cout << _MOVEMENT_MENU[8] << endl;
			else {

				m_board.popCard(colO, volteado);
				m_clubs[palo.getClub()].push(palo);
				m_nMoves++;
				m_score += _POINTS[2];

				if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
			}
		} else {

			if (palo > m_clubs[palo.getClub()].top()) {

				m_board.popCard(colO, volteado);
				m_clubs[palo.getClub()].push(palo);
				m_nMoves++;
				m_score += _POINTS[2];

				if (m_nMoves % 10 == 0) m_score -= _POINTS[0];

			} else
				cout << _MOVEMENT_MENU[8] << endl;
		}
		if (volteado) m_score += _POINTS[1];
	}
}

void Game::club2board() {

	int palo;
	cout << _MOVEMENT_MENU[9];
	cin  >> palo;
	palo--;

	if (palo < 0 || palo >= _CLUBS)
		cout << _MOVEMENT_MENU[10] << endl;
	else {

		if (m_clubs[palo].isEmpty())
			cout << _MOVEMENT_MENU[10] << endl;
		else {

			Card mov = m_clubs[palo].top();

			int colD;
			cout << _MOVEMENT_MENU[0];
			cin  >> colD;
			colD--;

			if (colD < 0 || colD > m_board.maxCol())
				cout << _MOVEMENT_MENU[1] << (colD + 1) << endl;
			else {

				if (!m_board.pushCard(mov, colD))
					cout << _MOVEMENT_MENU[1] << (colD + 1) << endl;
				else {
					m_clubs[palo].pop();
					m_nMoves++;
					m_score -= _POINTS[3];

					if (m_nMoves % 10 == 0) m_score -= _POINTS[0];
				}
			}
		}
	}
}

bool Game::isFinished() const {

	bool acabado = m_clubs[0].length() == 13 &&
			m_clubs[1].length() == 13 &&
			m_clubs[2].length() == 13 &&
			m_clubs[3].length() == 13;

	return acabado;
}

int Game::getMoves() const {
	return m_nMoves;
}

int Game::getScore() const {
	return m_score;
}

ostream &operator<<(ostream &o, const Game &g) {

	o << endl << g._STATUS_MENU[0] << endl;

	o << g._STATUS_MENU[8] << g.m_lastCards << endl;

	for (int i = 0; i < g._CLUBS; i++)
		o << g.m_clubs[i];

	o << "   ";

	for (int i = 0; i < g._HANDS; i++)
		o << g.m_hands[i];

	o << endl << g.m_board << endl;

	if (!g.isFinished()) {

		o << g._STATUS_MENU[1] << g._STATUS_MENU[2] << g.getMoves() << g._STATUS_MENU[3];
		o << g.m_clubs[0].length() << g._SEP << g.m_clubs[1].length() << g._SEP;
		o << g.m_clubs[2].length() << g._SEP << g.m_clubs[3].length();
		o << g._STATUS_MENU[4] << g._STATUS_MENU[5];
		o << g.m_hands[0].length() << g._SEP << g.m_hands[1].length();
		o << g._STATUS_MENU[6] << " " << g.getScore() << " POINTS" << endl;

	} else
		o << g._STATUS_MENU[7] << endl;

	return o;
}
