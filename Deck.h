/*
 * Deck.h
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#ifndef DECK_H_
#define DECK_H_
#include "Card.h"

// DESCRIPTION:	Clase que mezcla las 52 cartas de las que se compone un mazo
//				de cartas sin contar los comodines

// INVARIANT:	m_cardArray es un vector de 52 cartas

class Deck {

public:

	// CONSTRUCTORS

	// PRE:  --
	// POST: --
	Deck();

	// PRE:  sem > 0
	// POST: --
	Deck(const int &seed);

	// GETTERS

	// PRE: index > 0 && index < _LENGTH
	// POST: devuelve la carta en la posición index de m_cardArray
	Card getCard(const int &index) const;

private:

	// CONSTANTS
	static const int _CLUBS    = 4;
	static const int _NUMBERS  = 13;
	static const int _LENGTH = 52;
	static const int _BOARD_CARDS = 28;
	static const int _HAND_CARDS = 24;


	// ATTRIBUTES
	Card m_cardArray[_LENGTH];


	// SETTERS

	// PRE:  --
	// POST: 52 cartas que cumplen su INVARIANTE ordenadas de mayor a menor
	void initialize();

	// PRE:  --
	// POST: 52 cartas que cumplen su INVARIANTE mezcladas de orden
	void fisherYates();


	// STATIC CLASS METHODS
	static void plantSeed(const int &seed);

	static int randomizeSeed(int max);

	// STATIC CLASS ATTRIBUTE
	static unsigned m_seed;
};

#endif /* DECK_H_ */
