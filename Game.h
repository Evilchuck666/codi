/*
 * Game.h
 *
 *  Created on: 11 de jun. de 2016
 *      Author: evilchuck
 */

#ifndef GAME_H_
#define GAME_H_
#include "Deck.h"
#include "Stack.h"
#include "Board.h"
#include <iostream>
#include <string>
using namespace std;

// DESCRIPTION:	La clase Game, gestiona el tablero, así como las pilas de cada
//				palo y las pilas para robar cartas.
//				Al realizar una acción, la clase Game puede preguntar al
//				usuario, si el usuario se equivoca o intenta realizar un
//				movimiento ilegal, devolverá un mensaje de aviso y no
//				hará el movimiento

// INVARIANT:	Los atributos de las clases Stack y Board deben de cumplir
//				sus INVARIANTES, m_nMoves y a_abCartas deben de ser positivos

class Game {

public:

	// CONSTRUCTORS

	// PRE:  --
	// POST: --
	Game();

	// PRE:  --
	// POST: --
	Game(const Deck &deck, const int &open);


	// SETTERS (ACCIONES DEL JUEGO)

	// PRE:  --
	// POST: abre cartas
	void openCard();

	// PRE:  --
	// POST: mueve una carta de la mano al tablero
	void hand2board();

	// PRE:  --
	// POST: mueve una carta de la mano al montón de su palo
	void hand2club();

	// PRE:  --
	// POST: mueve una o mas cartas dentro del tablero
	void withinBoard();

	// PRE:  --
	// POST: mueve una carta del tablero al montón de su palo
	void board2club();

	// PRE:  --
	// POST: mueve una carta de un montón al tablero
	void club2board();


	// GETTERS

	// PRE:  --
	// POST: devuelve si el juego ha finalizado
	bool isFinished() const;

	// PRE:  --
	// POST: devuelve el número de jugadas ya realizadas
	int getMoves() const;

	// PRE:  --
	// POST: devuelve la puntuación
	int getScore() const;


	// FLUX OPERATORS

	// PRE:  --
	// POST: muestra las cartas descartadas,
	// POST: las pilas, el tablero y las estadísticas del juego
	friend ostream &operator<<(ostream &o, const Game &g);

private:

	// CONSTANTS
	static const int _MAX_CARDS = 52;

	static const int _COLS  = 7;
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
