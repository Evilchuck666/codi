/*
 * Card.h
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#ifndef CARD_H_
#define CARD_H_
#include <ostream>
#include <string>
using namespace std;

// DESCRIPTION:	Clase que guarda el palo y el numero asociado a la carta
// 				y si está o no isVisible.

// INVARIANT:	m_club debe tener un value entre 0 i 3 (ambos incluidos)
// INVARIANT:	m_number debe tener un value entre 0 i 12 (ambos incluidos)
// INVARIANT:	m_visible debe tener un value booleano

class Card {

public:

	// CONSTRUCTORS

	// PRE:  --
	// POST: --
	Card();

	// PRE:  p i n deben de ser valores positivos
	// POST: --
	Card(const int &p, const int &n);


	// PRE:  --
	// POST: copia los atributos de c al objeto actual
	Card(const Card &c);


	// GETTERS

	// PRE:  --
	// POST: devuelve el value de m_club
	int getClub()   const;

	// PRE:  --
	// POST: devuelve el value de m_number
	int getNumber() const;

	// PRE:  --
	// POST: devuelve el value de m_visible
	bool isVisible() const;

	// PRE:  --
	// POST: devuelve los valores de m_number y m_club respectivamente en
	//       formato string
	string toString() const;


	// SETTERS

	// PRE:  --
	// POST: cambia el value de m_visible
	void turn();


	// OPERATORS

	// PRE:  --
	// POST: compara dos cartas y devuelve si la
	//       primera es mayor que la segunda
	bool operator>(const Card &c) const;

	// PRE:  --
	// POST: compara dos cartas y devuelve si la
	//       primera es menor que la segunda
	bool operator<(const Card &c) const;

	// PRE:  --
	// POST: asigna los valores de la carta c al objeto actual
	Card &operator=(const Card &c);


private:

	// CONSTANTS
	static const int _N_CLUBS = 4;
	static const int _N_NUMBERS = 13;

	static const int _CH_COL = 3;

	static const char _CLUBS[_N_CLUBS];
	static const char _NUMBERS[_N_NUMBERS];


	// ATTRIBUTES
	int  m_club;
	int  m_number;
	bool m_visible;
	bool m_colour;
};

#endif /* CARD_H_ */
