/*
* Stack.h
*
*  Created on: 10 de jun. de 2016
*      Author: EvilChuck
*/

#ifndef STACK_H_
#define STACK_H_

#include "Card.h"
#include <ostream>

using namespace std;

// DESCRIPTION: Basic structure data of cards, you can push or pull
//              cards from the top (LIFO type; Last In First Out)

// INVARIANT: m_length >= 0 and m_top must agree its INVARIANT

class Stack {

public:

// CONSTRUCTORS

// PRE: --
// POST: --
    Stack();

// PRE: --
// POST: copies attributes from s to this
    Stack(const Stack &p);


// DESTRUCTOR

// PRE: --
// POST: m_length = 0 and m_top points to nullptr
    virtual ~Stack();


// GETTERS

// PRE: --
// POST: returns if the stack is empty
    bool isEmpty() const;

// PRE: --
// POST: returns stack length
    int length() const;

// PRE: --
// POST: returns the card of the top
    Card top() const;

// SETTERS

// PRE: --
// POST: adds c to the stack
    void push(const Card &c);

// PRE: --
// POST: pops the top card of the stack
    void pop();

// PRE: --
// POST: makes an inverse copy of s
    void inverseCopy(Stack s);

// PRE: --
// POST: frees the stack
    void release();


// OPERATORS

// PRE: --
// POST: sets attributes of s to this
    Stack &operator=(const Stack &s);

// FLUX OPERATORS

// PRE: --
// POST: prints the last card
    friend ostream &operator<<(ostream &o, const Stack &s);

private:

// INVARIANT: value must agree its Card INVARIANT
//            and previous must point to another valid Node,
//            if it is the last Node, then previous points to nullptr
    struct Node {

        Card value;
        Node *previous;
    };

// ATTRIBUTES
    Node *m_top;

    int m_length;

// PRIVATE METHODS

// PRE: --
// POST: clones s to this
    void clone(const Stack &s);
};
#endif /* STACK_H_ */
