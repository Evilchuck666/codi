/*
 * Pila.h
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#ifndef PILA_H_
#define PILA_H_
#include "Carta.h"
#include <ostream>
using namespace std;

// DESCRIPCIÓN:	Estructura básica de datos, que va añadiendo
//				o quitando cartas del montón (tipo LIFO; Last In First Out)

// INVARIANTE:	a_largo >= 0 y a_cima debe cumplir su INVARIANTE

class Pila {

public:

	// CONSTRUCTORES

	// PRE:  --
	// POST: --
	Pila();

	// PRE:  --
	// POST: copia los atributos de s al objeto actual
	Pila(const Pila &p);


	// DESTRUCTOR

	// PRE:  --
	// POST: a_largo = 0 y a_cima apunta a NULO
	virtual ~Pila();


	// MÉTODOS CONSULTORES

	// PRE:  --
	// POST: devuelve si la pila está vacía
	bool vacio() const;

	// PRE:  --
	// POST: devuelve el número de cartas acumalada a la pila
	int largo() const;

	// PRE:  --
	// POST: devuelve la última carta, la que está en la cima
	Carta cima() const;

	// MÉTODOS MODIFICADORES

	// PRE:  --
	// POST: Añade c a la pila
	void apilar(const Carta &c);

	// PRE:  --
	// POST: retira la carta superior de la pila
	void retirar();

	// PRE:  --
	// POST: hace una copia inversa de s
	void copInv(Pila s);

	// PRE:  --
	// POST: borra de la pila todas las cartas
	void liberar();


	// OPERADORES

	// PRE:  --
	// POST: asigna los atributos de s al objeto actual
	Pila &operator=(const Pila &s);

	// OPERADORES DE FLUJO

	// PRE:  --
	// POST: muestra la última carta
	friend ostream &operator<<(ostream &o, const Pila &s);

private:

	// INVARIANTE:	valor debe cumplir la INVARIANTE de Carta
	//				y ant debe apuntar a otro Nodo válido,
	//				en caso de ser el último nodo de la pila, apunta a NULL
	struct Nodo {

		Carta valor;
		Nodo *ant;
	};

	// ATRIBUTOS
	Nodo *a_cima;

	int a_largo;

	// MÉTODOS PRIVADOS

	// PRE:  --
	// POST: hace una copia exacta de s, respetando el orden de los nodos
	void clonar(const Pila &s);
};

#endif /* PILA_H_ */
