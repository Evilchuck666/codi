//============================================================================
// Name        : main.cpp
// Author      : EvilChuck
// Version     : v0.666
// Copyright   : SatanicWorks
// Description : Solitario en versión consola
//============================================================================

#include <iostream>
#include "Baraja.h"
#include "Juego.h"
using namespace std;

// PRE:  --
// POST: sem > 0
void leerPasos(int &sem) {

	do
	{
		cout << "ENTRA UNA LLAVOR POSITIVA: ";
		cin  >> sem;

	} while (sem <= 0);
}

// PRE:  --
// POST: abrir == 1 || abrir == 2
void abrirCartas(int &abrir) {

	do {

		cout << "QUANTES CARTES VOLS OBRIR?" << endl;
		cout << "1.- D'UNA EN UNA"           << endl;
		cout << "2.- DE TRES EN TRES"        << endl;
		cin  >> abrir;

	} while (!(abrir > 0 && abrir < 3));

	if (abrir == 2) abrir = 3;
}

// PRE:  --
// POST: --
void menu(const int &abrir) {

	cout << "MENU" << endl;

	if (abrir == 1)
		cout << "1. OBRIR UNA CARTA (O TORNAR A COMENCAR)" << endl;
	else
		cout << "1. OBRIR TRES CARTES (O TORNAR A COMENCAR)" << endl;

	cout << "2. POSAR UNA CARTA (MA->TAULER)"          << endl;
	cout << "3. POSAR UNA CARTA (MA->PILA)"            << endl;
	cout << "4. MOURE UNA CARTA (TAULER->TAULER)"      << endl;
	cout << "5. MOURE UNA CARTA (TAULER->PILA)"        << endl;
	cout << "6. RECUPERAR UNA CARTA (PILA->TAULER)"    << endl;
	cout << "9. MOSTRAR MENU"                          << endl;
	cout << "0. ABANDONAR LA PARTIDA"                  << endl;
}


// DESCRIPCION: Lee una semilla de valor positivo, immediatamente pide
// 				si quieres destapar las cartas de una en una o de tres en tres.
//				Una vez introducidos estos datos, empieza el juego, mostrandote
//				primero el estado del tablero y mostrando el menú de opciones.
//				Si escribimos una opción no mostrada en el menú se
//				quejará sin realizar acción alguna, en el caso de que le
//				pidamos una opción legal, intentará realizarla según las reglas
//				del juego, y nuevamente se quejará en caso de que el movimiento
//				se considere ilegal.
//				El juego acaba cuando todas las cartas estan en la montón de
//				su respectivo palo, o cuando el usuario decide abandonar.
//				El juego se basa en las reglas básicas del solitario.

int main() {

	int sem;
	int abrir;

	leerPasos(sem);
	abrirCartas(abrir);

	Baraja bar(sem);

	Juego juego(bar, abrir);

	cout << juego << endl;
	menu(abrir);

	int opcion;
	cout << "OPCIO: ";
	cin  >> opcion;

	while (opcion != 0 && !juego.acabado()) {

		if      (opcion == 1) juego.abrirCarta();
		else if (opcion == 2) juego.manTablero();
		else if (opcion == 3) juego.manoAlPalo();
		else if (opcion == 4) juego.tablAlTabl();
		else if (opcion == 5) juego.tablAlPalo();
		else if (opcion == 6) juego.paloAlTabl();
		else if (opcion == 9) menu(abrir);
		else {

			cout << "OPCIO NO DEFINIDA " << opcion << endl;
			menu(abrir);
		}

		if (opcion != 9) cout << juego << endl;

		if (!juego.acabado()) {

			cout << "OPCIO: ";
			cin  >> opcion;
		}
	}

	if (!juego.acabado())
		cout << "PARTIDA ABANDONADA" << endl;
	else {
		cout << "PARTIDA GUANYADA AMB " << juego.getJugadas()    << " JUGADES";
		cout << " AMB UN TOTAL DE "     << juego.getPuntuacion() << " PUNTS" << endl;
	}

	return 0;
}
