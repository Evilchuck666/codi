/*
 * Tablero.cpp
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#include "Tablero.h"
#include "Pila.h"

void Tablero::inicializar(const int &cols) {

	a_cols    = cols;
	a_nCartas = 0;

	a_longitud    = new int[a_cols];
	a_longitudMax = new int[a_cols];

	crearVector();
	crearMatriz();
}

void Tablero::crearVector() {

	for (int i = 0; i < a_cols; i++) {

		a_longitud[i]    = (i + 1);
		a_longitudMax[i] = (i + _CART_PALO);
	}
}

void Tablero::crearMatriz() {

	a_tablero = new Carta*[a_cols];

	for (int i = 0; i < a_cols; i++)
		a_tablero[i] = new Carta[a_longitudMax[i]];
}

void Tablero::rellMatriz(const Baraja &bar) {

	for (int i = 0; i < a_cols; i++) {

		int max = a_longitud[(a_cols - 1) - i];

		for (int j = 0; j < max; j++) {

			a_tablero[j + i][i] = bar.getCarta(a_nCartas);
			a_nCartas++;
		}
	}
}

void Tablero::voltearCartas() {

	for (int i = 0; i < a_cols; i++)
		a_tablero[i][a_longitud[i] - 1].voltear();
}

void Tablero::clonar(const Tablero &t) {

	inicializar(t.a_cols);

	for (int i = 0; i < a_cols; i++) {

		a_longitud[i]    = t.a_longitud[i];
		a_longitudMax[i] = t.a_longitudMax[i];

		for (int j = 0; j < a_longitud[i]; j++)
			a_tablero[i][j] = t.getCarta(i,j);
	}
	a_nCartas = t.a_nCartas;
}


Tablero::Tablero() {

	int cols = _COLS_DEF;
	inicializar(cols);
}

Tablero::Tablero(const Baraja &bar, const int &cols) {

	inicializar(cols);
	rellMatriz(bar);
	voltearCartas();
}

Tablero::Tablero(const Tablero &t) {

	inicializar(t.a_cols);
	clonar(t);
}


int Tablero::nCartas() const {
	return a_nCartas;
}

int Tablero::maxCol() const {
	return (a_cols - 1);
}

Carta Tablero::getCarta(const int &colO, const int &filaO) const {
	return a_tablero[colO][filaO];
}

int Tablero::getLongitud(const int &col) const {
	return a_longitud[col];
}

bool Tablero::colCarta(const Carta &c, const int &col) {

	if (a_longitud[col] < a_longitudMax[col]) {

		if (a_longitud[col] > 0) {

			Carta previa = a_tablero[col][a_longitud[col] - 1];

			if (c < previa) {

				a_tablero[col][a_longitud[col]] = c;
				a_longitud[col]++;

			} else return false;

		} else {

			if (c.getNumero() == 12) {

				a_tablero[col][0] = c;
				a_longitud[col]++;

			} else
				return false;
		}

	} else return false;

	return true;
}

bool Tablero::retCarta(const int &col, bool &volteado) {

	if (a_longitud[col] == 0) return false;

	a_longitud[col]--;

	Carta volt = a_tablero[col][a_longitud[col] - 1];

	if (!volt.visible()) {

		a_tablero[col][a_longitud[col] - 1].voltear();
		volteado = true;
	}

	return true;
}

void Tablero::mov(const int &colO, const int &filaO, const int &colD, bool &volteado) {

	Pila tmp;

	for (int i = (a_longitud[colO] - 1); i >= filaO; i--) {

		tmp.apilar(a_tablero[colO][i]);
		retCarta(colO, volteado);
	}

	int longNueva = a_longitud[colD] + tmp.largo();

	for (int i = a_longitud[colD]; i < longNueva; i++) {

		colCarta(tmp.cima(), colD);
		tmp.retirar();
	}
}

bool Tablero::movCarta(const int &colO, const int &filaO, const int &colD, bool &volteado) {

	if (a_longitud[colD] == 0) {

		if (a_tablero[colO][filaO].getNumero() != 12)
			return false;
		else
			mov(colO, filaO, colD, volteado);
	} else {

		Carta mayor = a_tablero[colD][a_longitud[colD] - 1];
		Carta menor = a_tablero[colO][filaO];

		if (!(menor < mayor))
			return false;
		else
			mov(colO, filaO, colD, volteado);
	}
	return true;
}

Tablero &Tablero::operator =(const Tablero &t) {

	crearVector();
	crearMatriz();
	clonar(t);

	return *this;
}

ostream &operator<<(ostream &o, const Tablero &t) {

	for (int c = 1; c <= t.a_cols; c++)
		o << "c" << c << " ";
	o << endl;

	int filas = t.filaLarga();

	for (int f = 0; f < filas; f++) {

		for (int j = 0; j < t.a_cols; j++) {

			int tab = t.a_longitud[j];

			if (f < tab)
				o << t.a_tablero[j][f].toString() << " ";
			else
				o << "   ";
		}
		o << "f" << (f + 1) << endl;
	}
	return o;
}

int Tablero::filaLarga() const {

	int max = 0;

	for (int i = 0; i < a_cols; i++) {

		if (a_longitud[i] > max)
			max = a_longitud[i];
	}

	return max;
}
