/*
 * Board.h
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#ifndef BOARD_H_
#define BOARD_H_
#include "Deck.h"
#include "Card.h"
#include <ostream>

// DESCRIPTION:	Gestiona y muestra la disposición de las cartas en el tablero,
//				así como comprueba que los movimientos sean legales, en caso
//				contrario, aborta el movimiento.

// INVARIANT:	El atributo m_board debe cumplir la INVARIANTE de la clase
//				Card, los atributos de tipo entero deben ser positivos.

class Board {

public:

	// INITIALIZER

	// PRE:  --
	// POST: Llena la matriz dinámica m_board con las cartas de la baraja
	void fillMatrix(const Deck &deck);


	// CONSTRUCTORS

	// PRE:  --
	// POST: --
	Board();

	// PRE:  --
	// POST: cols > 0
	Board(const Deck &deck, const int &cols);

	// PRE:  --
	// POST: copia t al objeto actual
	Board(const Board &b);


	// GETTERS

	// PRE:  --
	// POST: devuelve el total de cartas utilizadas al crear el tablero inicial
	int nCards() const;

	// PRE:  --
	// POST: devuelve el número de columnas que utiliza el tablero
	int maxCol()  const;

	// PRE:  colO debe estar entre 0 y maxCol()
	// PRE:  filaO debe estar entre 0 y m_length[colO] - 1
	// POST: devuelve la carta posicionada en colO, filaO de m_board
	Card getCard(const int &srcCol, const int &srcRow) const;

	// PRE:  col debe estar entre 0 y maxCol()
	// POST: devuelve el número de Cartas (longitud), asignadas a col
	int getLength(const int &col) const;


	// SETTERS

	// PRE:  col debe estar entre 0 y maxCol()
	// POST: devuelve cierto si puede añadir la carta, falso en caso contrario
	bool pushCard(const Card &c, const int &col);

	// PRE:  col debe estar entre 0 y maxCol(), volteado debe ser una variable
	// POST: devuelve cierto si puede pop la carta, falso en caso contrario
	bool popCard(const int &col, bool &turned);

	// PRE:  colO y colD deben estar entre 0 y maxCol(),
	// PRE:  filaO debe estar entre 0 y m_length[colO] - 1, volteado tiene
	// PRE:  que ser una variable
	// POST: devuelve cierto si puede mover las cartas desde colO, filaO a colD
	bool moveCard(const int &srcCol, const int &srcRow, const int &dstCol, bool &turned);


	// OPERATORS

	// PRE:  --
	// POST: asigna los valores de los atributos de t al objeto actual
	Board &operator=(const Board &b);


	// FLUX OPERATORS

	// PRE:  --
	// POST: muestra la disposición de las cartas en el tablero
	friend ostream &operator<<(ostream &o, const Board &b);

private:

	// CONSTANTS
	static const int _DEFAULT_COLUMNS  = 7;
	static const int _MAX_ROWS = 19;
	static const int _CLUB_CARDS = 13;


	// ATTRIBUTES
	Card **m_board;

	int *m_length;
	int *m_maxLength;

	int m_cols;

	int m_nCards;


	// PRIVATE METHODS

	// PRE:  cols > 0
	// POST: crea la estructura básica del tablero
	void initialize(const int &cols);

	// PRE:  --
	// POST: asigna las longitudes iniciales y máxima de cada columna a
	// POST: m_length y m_maxLength respectivamente
	void createArray();

	// PRE:  --
	// POST: crea la matriz m_board
	void createMatrix();

	// PRE:  --
	// POST: gira la última carta de cada columna del tablero
	void turnCards();

	// PRE:  --
	// POST: hace una copia de t
	void clone(const Board &b);

	// PRE:  colO y colD deben de tener un value entre o y maxCol()
	// PRE:  filaO debe tener un value entre 0 y m_length[colO],
	// PRE:  volteado debe de ser una variable
	// POST: mueve todas las cartas desde colO, filaO a colD
	void move(const int &srcCol, const int &srcRow, const int &dstCol, bool &turned);

	// PRE:  --
	// POST: devuelve la fila más larga
	int longestRow() const;

};

#endif /* BOARD_H_ */
