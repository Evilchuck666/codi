/*
 * Carta.h
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#ifndef CARTA_H_
#define CARTA_H_
#include <ostream>
#include <string>
using namespace std;

// DESCRIPCIÓN:	Clase que guarda el palo y el numero asociado a la carta
// 				y si está o no visible.

// INVARIANTE:	a_palo debe tener un valor entre 0 i 3 (ambos incluidos)
// INVARIANTE:	a_numero debe tener un valor entre 0 i 12 (ambos incluidos)
// INVARIANTE:	a_visible debe tener un valor booleano

class Carta {

public:

	// CONSTRUCTORES

	// PRE:  --
	// POST: --
	Carta();

	// PRE:  p i n deben de ser valores positivos
	// POST: --
	Carta(const int &p, const int &n);


	// PRE:  --
	// POST: copia los atributos de c al objeto actual
	Carta(const Carta &c);


	// MÉTODOS CONSULTORES

	// PRE:  --
	// POST: devuelve el valor de a_palo
	int getPalo()   const;

	// PRE:  --
	// POST: devuelve el valor de a_numero
	int getNumero() const;

	// PRE:  --
	// POST: devuelve el valor de a_visible
	bool visible() const;

	// PRE:  --
	// POST: devuelve los valores de a_numero y a_palo respectivamente en
	//       formato string
	string toString() const;


	// MÉTODOS MODIFICADORES

	// PRE:  --
	// POST: cambia el valor de a_visible
	void voltear();


	// OPERADORES

	// PRE:  --
	// POST: compara dos cartas y devuelve si la
	//       primera es mayor que la segunda
	bool operator>(const Carta &c) const;

	// PRE:  --
	// POST: compara dos cartas y devuelve si la
	//       primera es menor que la segunda
	bool operator<(const Carta &c) const;

	// PRE:  --
	// POST: asigna los valores de la carta c al objeto actual
	Carta &operator=(const Carta &c);


private:

	// CONSTANTES
	static const int _N_PALOS = 4;
	static const int _N_NUMRS = 13;

	static const int _CAM_COL = 3;

	static const char _PALOS[_N_PALOS];
	static const char _NUMEROS[_N_NUMRS];


	// ATRIBUTOS
	int  a_palo;
	int  a_numero;
	bool a_visible;
	bool a_color;
};

#endif /* CARTA_H_ */
