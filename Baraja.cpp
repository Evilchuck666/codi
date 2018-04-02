/*
 * Baraja.cpp
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#include <cstdlib>
#include "Baraja.h"
using namespace std;

unsigned Baraja::a_sem = 1;

void Baraja::inicializar() {

	int k = 0;

	for (int i = (_PALOS - 1); i >= 0; i--) {

		for (int j = (_NUMEROS - 1); j >= 0; j--) {

			a_vector[k] = Carta(i,j);
			k++;
		}
	}
}

void Baraja::fisherYates() {

	// Variante Sattolo del algoritmo de Fisher-Yates

	for (int k = (_LONGITUD - 1); k > 1; k--) {

		int az = aleatorio(k - 1);

		Carta tmp = a_vector[az];
		a_vector[az] = a_vector[k];
		a_vector[k] = tmp;
	}
}

Baraja::Baraja() {

	Baraja::semilla(0);

	inicializar();
	fisherYates();
}

Baraja::Baraja(const int &sem) {

	Baraja::semilla(sem);

	inicializar();
	fisherYates();
}

Carta Baraja::getCarta(const int &index) const {
	return a_vector[index];
}

void Baraja::semilla(const int &sem) {

	a_sem = abs(sem);

	if (a_sem == 0) a_sem++;
}

int Baraja::aleatorio(int max) {

	a_sem = a_sem * 1103515245 + 12345;
	int res = (a_sem / 32) % 32768;

	return res % max;
}
