/*
 * Juego.h
 *
 *  Created on: 11 de jun. de 2016
 *      Author: evilchuck
 */

#ifndef JUEGO_H_
#define JUEGO_H_
#include "Baraja.h"
#include "Pila.h"
#include "Tablero.h"
#include <iostream>
#include <string>
using namespace std;

// DESCRIPCIÓN:	La clase Juego, gestiona el tablero, así como las pilas de cada
//				palo y las pilas para robar cartas.
//				Al realizar una acción, la clase Juego puede preguntar al
//				usuario, si el usuario se equivoca o intenta realizar un
//				movimiento ilegal, devolverá un mensaje de aviso y no
//				hará el movimiento

// INVARIANTE:	Los atributos de las clases Pila y Tablero deben de cumplir
//				sus INVARIANTES, a_nJugadas y a_abCartas deben de ser positivos

class Juego {

public:

	// CONSTRUCTORES

	// PRE:  --
	// POST: --
	Juego();

	// PRE:  --
	// POST: --
	Juego(const Baraja &bar, const int &abrir);


	// MÉTODOS MODIFICADORES (ACCIONES DEL JUEGO)

	// PRE:  --
	// POST: abre cartas
	void abrirCarta();

	// PRE:  --
	// POST: mueve una carta de la mano al tablero
	void manTablero();

	// PRE:  --
	// POST: mueve una carta de la mano al montón de su palo
	void manoAlPalo();

	// PRE:  --
	// POST: mueve una o mas cartas dentro del tablero
	void tablAlTabl();

	// PRE:  --
	// POST: mueve una carta del tablero al montón de su palo
	void tablAlPalo();

	// PRE:  --
	// POST: mueve una carta de un montón al tablero
	void paloAlTabl();


	// MÉTODOS CONSULTORES

	// PRE:  --
	// POST: devuelve si el juego ha finalizado
	bool acabado() const;

	// PRE:  --
	// POST: devuelve el número de jugadas ya realizadas
	int getJugadas() const;

	// PRE:  --
	// POST: devuelve la puntuación
	int getPuntuacion() const;


	// OPERADORES DE FLUJO

	// PRE:  --
	// POST: muestra las cartas descartadas,
	// POST: las pilas, el tablero y las estadísticas del juego
	friend ostream &operator<<(ostream &o, const Juego &j);

private:

	// CONSTANTES
	static const int _MAX_CARTAS = 52;

	static const int _COLS  = 7;
	static const int _PALOS = 4;
	static const int _MANOS = 2;

	static const int _PUNT[5];

	static const char _SEP = ',';
	static const string _MEN_MOV[11];
	static const string _MEN_JUG[9];


	// ATRIBUTOS
	Pila a_manos[_MANOS];
	Pila a_palos[_PALOS];

	Tablero a_tablero;

	int a_nJugadas;
	int a_puntuacion;
	int a_abNCartas;

	string a_ultimasCartas;
};

#endif /* JUEGO_H_ */
