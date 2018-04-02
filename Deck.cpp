/*
 * Deck.cpp
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#include <cstdlib>
#include "Deck.h"
using namespace std;

unsigned Deck::m_seed = 1;

void Deck::initialize() {

	int k = 0;

	for (int i = (_CLUBS - 1); i >= 0; i--) {

		for (int j = (_NUMBERS - 1); j >= 0; j--) {

			m_cardArray[k] = Card(i,j);
			k++;
		}
	}
}

void Deck::fisherYates() {

	// Variante Sattolo del algoritmo de Fisher-Yates

	for (int k = (_LENGTH - 1); k > 1; k--) {

		int az = randomizeSeed(k - 1);

		Card tmp = m_cardArray[az];
		m_cardArray[az] = m_cardArray[k];
		m_cardArray[k] = tmp;
	}
}

Deck::Deck() {

    Deck::plantSeed(0);

    initialize();
	fisherYates();
}

Deck::Deck(const int &seed) {

    Deck::plantSeed(seed);

    initialize();
	fisherYates();
}

Card Deck::getCard(const int &index) const {
	return m_cardArray[index];
}

void Deck::plantSeed(const int &seed) {

	m_seed = abs(seed);

	if (m_seed == 0) m_seed++;
}

int Deck::randomizeSeed(int max) {

	m_seed = m_seed * 1103515245 + 12345;
	int res = (m_seed / 32) % 32768;

	return res % max;
}
