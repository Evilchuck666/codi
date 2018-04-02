/*
 * Baraja.h
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#ifndef BARAJA_H_
#define BARAJA_H_
#include "Carta.h"

// DESCRIPCIÓN:	Clase que mezcla las 52 cartas de las que se compone un mazo
//				de cartas sin contar los comodines

// INVARIANTE:	a_vector es un vector de 52 cartas

class Baraja {

public:

	// CONSTRUCTORES

	// PRE:  --
	// POST: --
	Baraja();

	// PRE:  sem > 0
	// POST: --
	Baraja(const int &sem);

	// METODOS CONSULTORES

	// PRE: index > 0 && index < _LONGITUD
	// POST: devuelve la carta en la posición index de a_vector
	Carta getCarta(const int &index) const;

private:

	// CONSTANTES
	static const int _PALOS    = 4;
	static const int _NUMEROS  = 13;
	static const int _LONGITUD = 52;
	static const int _CAR_TABL = 28;
	static const int _CAR_MANO = 24;


	// ATRIBUTOS
	Carta a_vector[_LONGITUD];


	// MÉTODOS MODIFICADORES

	// PRE:  --
	// POST: 52 cartas que cumplen su INVARIANTE ordenadas de mayor a menor
	void inicializar();

	// PRE:  --
	// POST: 52 cartas que cumplen su INVARIANTE mezcladas de orden
	void fisherYates();


	// MÉTODOS ESTÁTICOS DE CLASE
	static void semilla(const int &sem);

	static int aleatorio(int max);

	// ATRIBUTO ESTÁTICO DE CLASE
	static unsigned a_sem;
};

#endif /* BARAJA_H_ */
