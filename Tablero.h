/*
 * Tablero.h
 *
 *  Created on: 10 de jun. de 2016
 *      Author: evilchuck
 */

#ifndef TABLERO_H_
#define TABLERO_H_
#include "Baraja.h"
#include "Carta.h"
#include <ostream>

// DESCRIPCIÓN:	Gestiona y muestra la disposición de las cartas en el tablero,
//				así como comprueba que los movimientos sean legales, en caso
//				contrario, aborta el movimiento.

// INVARIANTE:	El atributo a_tablero debe cumplir la INVARIANTE de la clase
//				Carta, los atributos de tipo entero deben ser positivos.

class Tablero {

public:

	// INICIALIZADOR

	// PRE:  --
	// POST: Llena la matriz dinámica a_tablero con las cartas de la baraja
	void rellMatriz(const Baraja &bar);


	// CONSTRUCTORES

	// PRE:  --
	// POST: --
	Tablero();

	// PRE:  --
	// POST: cols > 0
	Tablero(const Baraja &bar, const int &cols);

	// PRE:  --
	// POST: copia t al objeto actual
	Tablero(const Tablero &t);


	// MÉTODOS CONSULTORES

	// PRE:  --
	// POST: devuelve el total de cartas utilizadas al crear el tablero inicial
	int nCartas() const;

	// PRE:  --
	// POST: devuelve el número de columnas que utiliza el tablero
	int maxCol()  const;

	// PRE:  colO debe estar entre 0 y maxCol()
	// PRE:  filaO debe estar entre 0 y a_longitud[colO] - 1
	// POST: devuelve la carta posicionada en colO, filaO de a_tablero
	Carta getCarta(const int &colO, const int &filaO) const;

	// PRE:  col debe estar entre 0 y maxCol()
	// POST: devuelve el número de Cartas (longitud), asignadas a col
	int getLongitud(const int &col) const;


	// MÉTODOOS MODIFICADORES

	// PRE:  col debe estar entre 0 y maxCol()
	// POST: devuelve cierto si puede añadir la carta, falso en caso contrario
	bool colCarta(const Carta &c, const int &col);

	// PRE:  col debe estar entre 0 y maxCol(), volteado debe ser una variable
	// POST: devuelve cierto si puede retirar la carta, falso en caso contrario
	bool retCarta(const int &col, bool &volteado);

	// PRE:  colO y colD deben estar entre 0 y maxCol(),
	// PRE:  filaO debe estar entre 0 y a_longitud[colO] - 1, volteado tiene
	// PRE:  que ser una variable
	// POST: devuelve cierto si puede mover las cartas desde colO, filaO a colD
	bool movCarta(const int &colO, const int &filaO, const int &colD, bool &volteado);


	// OPERADORES

	// PRE:  --
	// POST: asigna los valores de los atributos de t al objeto actual
	Tablero &operator=(const Tablero &t);


	// OPERADORES DE FLUJO

	// PRE:  --
	// POST: muestra la disposición de las cartas en el tablero
	friend ostream &operator<<(ostream &o, const Tablero &t);

private:

	// CONSTANTES
	static const int _COLS_DEF  = 7;
	static const int _MAX_FILAS = 19;
	static const int _CART_PALO = 13;


	// ATRIBUTOS
	Carta **a_tablero;

	int *a_longitud;
	int *a_longitudMax;

	int a_cols;

	int a_nCartas;


	// MÉTODOS PRIVADOS

	// PRE:  cols > 0
	// POST: crea la estructura básica del tablero
	void inicializar(const int &cols);

	// PRE:  --
	// POST: asigna las longitudes iniciales y máxima de cada columna a
	// POST: a_longitud y a_longitudMax respectivamente
	void crearVector();

	// PRE:  --
	// POST: crea la matriz a_tablero
	void crearMatriz();

	// PRE:  --
	// POST: gira la última carta de cada columna del tablero
	void voltearCartas();

	// PRE:  --
	// POST: hace una copia de t
	void clonar(const Tablero &t);

	// PRE:  colO y colD deben de tener un valor entre o y maxCol()
	// PRE:  filaO debe tener un valor entre 0 y a_longitud[colO],
	// PRE:  volteado debe de ser una variable
	// POST: mueve todas las cartas desde colO, filaO a colD
	void mov(const int &colO, const int &filaO, const int &colD, bool &volteado);

	// PRE:  --
	// POST: devuelve la fila más larga
	int filaLarga() const;

};

#endif /* TABLERO_H_ */
