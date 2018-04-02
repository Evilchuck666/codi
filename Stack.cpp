/*
 * Stack.cpp
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#include "Stack.h"

Stack::Stack() {
	m_top  = NULL;
	m_length = 0;
}

Stack::Stack(const Stack &s) {
	clone(s);
}

Stack::~Stack() {
	release();
}

bool Stack::isEmpty() const {
	return m_top == NULL;
}

int Stack::length() const {
	return m_length;
}

Card Stack::top() const {
	return m_top->value;
}

void Stack::push(const Card &c) {

	Node *top = new Node;
	top->value = c;
	top->previous = m_top;

	m_top = top;

	m_length++;
}

void Stack::pop() {

	m_length--;
	Node *aux = m_top;
	m_top = m_top->previous;
	delete aux;
}

void Stack::inverseCopy(Stack s) {

	release();

	int max = s.m_length;
	for (int i = 0; i < max; i++) {

		Card c = s.top();
        c.turn();
		push(c);
		s.pop();
	}
}

void Stack::release() {

	while (!isEmpty()) {

		pop();
	}
}

Stack &Stack::operator=(const Stack &s) {

	clone(s);

	return *this;
}

ostream &operator<<(ostream &o, const Stack &s) {

	if (!s.isEmpty())
		o << s.top().toString();
	else
		o << "  ";

	o << " ";

	return o;
}

void Stack::clone(const Stack &s) {

	if (this != &s && !s.isEmpty()) {

		m_length = s.m_length;

		Node *q   = new Node;
		Node *p   = s.m_top;
		Node *ant = q;

		m_top = ant;

		q->value = p->value;
		q->previous   = NULL;

		p = p->previous;

		while (p != NULL) {

			q = new Node;
			q->value = p->value;
			q->previous = NULL;

			ant->previous = q;
			ant = q;
			p = p->previous;
		}
	}
}
