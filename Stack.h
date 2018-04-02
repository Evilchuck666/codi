/*
 * Stack.h
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#ifndef STACK_H_
#define STACK_H_
#include "Card.h"
#include <ostream>
using namespace std;

// DESCRIPTION:	Estructura básica de datos, que va añadiendo
//				o quitando cartas del montón (tipo LIFO; Last In First Out)

// INVARIANT:	m_length >= 0 y m_top debe cumplir su INVARIANTE

class Stack {

public:

	// CONSTRUCTORS

	// PRE:  --
	// POST: --
	Stack();

	// PRE:  --
	// POST: copia los atributos de s al objeto actual
	Stack(const Stack &p);


	// DESTRUCTOR

	// PRE:  --
	// POST: m_length = 0 y m_top apunta a NULO
	virtual ~Stack();


	// GETTERS

	// PRE:  --
	// POST: devuelve si la pila está vacía
	bool isEmpty() const;

	// PRE:  --
	// POST: devuelve el número de cartas acumalada a la pila
	int length() const;

	// PRE:  --
	// POST: devuelve la última carta, la que está en la top
	Card top() const;

	// SETTERS

	// PRE:  --
	// POST: Añade c a la pila
	void push(const Card &c);

	// PRE:  --
	// POST: retira la carta superior de la pila
	void pop();

	// PRE:  --
	// POST: hace una copia inversa de s
	void inverseCopy(Stack s);

	// PRE:  --
	// POST: borra de la pila todas las cartas
	void release();


	// OPERATORS

	// PRE:  --
	// POST: asigna los atributos de s al objeto actual
	Stack &operator=(const Stack &s);

	// FLUX OPERATORS

	// PRE:  --
	// POST: muestra la última carta
	friend ostream &operator<<(ostream &o, const Stack &s);

private:

	// INVARIANT:	value debe cumplir la INVARIANTE de Card
	//				y previous debe apuntar a otro Node válido,
	//				en caso de ser el último nodo de la pila, apunta a NULL
	struct Node {

		Card value;
		Node *previous;
	};

	// ATTRIBUTES
	Node *m_top;

	int m_length;

	// PRIVATE METHODS

	// PRE:  --
	// POST: hace una copia exacta de s, respetando el orden de los nodos
	void clone(const Stack &s);
};

#endif /* STACK_H_ */
