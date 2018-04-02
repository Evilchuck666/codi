/*
 * Carta.cpp
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#include "Carta.h"


const char Carta::_PALOS[_N_PALOS]   = {	'P', 'c', 'd', 'T'	};
const char Carta::_NUMEROS[_N_NUMRS] = {	'A', '2', '3', '4', '5',
											'6', '7', '8', '9', 'D',
											'J', 'Q', 'K'	};


Carta::Carta() {
	*this = Carta(0,0);
}

Carta::Carta(const int &p, const int &n) {

	a_palo    = p;
	a_numero  = n;
	a_visible = false;
	a_color   = a_palo % _CAM_COL != 0;
}

Carta::Carta(const Carta &c) {
	*this = c;
}


int Carta::getPalo() const {
	return a_palo;
}

int Carta::getNumero() const {
	return a_numero;
}

bool Carta::visible() const {
	return a_visible;
}

string Carta::toString() const {

	string str = "";

	if (a_visible) {

		str += _NUMEROS[a_numero];
		str += _PALOS[a_palo];

	} else str += "**";

	return str;
}


void Carta::voltear() {
	a_visible = !a_visible;
}


bool Carta::operator<(const Carta &c) const {
	return a_color != c.a_color && a_numero == (c.a_numero - 1);
}

bool Carta::operator>(const Carta &c) const {
	return a_palo == c.a_palo && a_numero == (c.a_numero + 1);
}

Carta &Carta::operator=(const Carta &c) {

	if (this != &c) {

		a_palo    = c.a_palo;
		a_numero  = c.a_numero;
		a_visible = c.a_visible;
		a_color   = c.a_color;
	}
	return *this;
}
