/*
 * Pila.cpp
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#include "Pila.h"

#include <iostream>

Pila::Pila() {
	a_cima  = NULL;
	a_largo = 0;
}

Pila::Pila(const Pila &s) {
	clonar(s);
}

Pila::~Pila() {
	liberar();
}

bool Pila::vacio() const {
	return a_cima == NULL;
}

int Pila::largo() const {
	return a_largo;
}

Carta Pila::cima() const {
	return a_cima->valor;
}

void Pila::apilar(const Carta &c) {

	Nodo *top = new Nodo;
	top->valor = c;
	top->ant = a_cima;

	a_cima = top;

	a_largo++;
}

void Pila::retirar() {

	a_largo--;
	Nodo *aux = a_cima;
	a_cima = a_cima->ant;
	delete aux;
}

void Pila::copInv(Pila s) {

	liberar();

	int max = s.a_largo;
	for (int i = 0; i < max; i++) {

		Carta c = s.cima();
		c.voltear();
		apilar(c);
		s.retirar();
	}
}

void Pila::liberar() {

	while (!vacio()) {

		retirar();
	}
}

Pila &Pila::operator=(const Pila &s) {

	clonar(s);

	return *this;
}

ostream &operator<<(ostream &o, const Pila &s) {

	if (!s.vacio())
		o << s.cima().toString();
	else
		o << "  ";

	o << " ";

	return o;
}

void Pila::clonar(const Pila &s) {

	if (this != &s && !s.vacio()) {

		a_largo = s.a_largo;

		Nodo *q   = new Nodo;
		Nodo *p   = s.a_cima;
		Nodo *ant = q;

		a_cima = ant;

		q->valor = p->valor;
		q->ant   = NULL;

		p = p->ant;

		while (p != NULL) {

			q = new Nodo;
			q->valor = p->valor;
			q->ant = NULL;

			ant->ant = q;
			ant = q;
			p = p->ant;
		}
	}
}
