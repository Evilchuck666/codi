//============================================================================
// Name        : main.cpp
// Author      : EvilChuck
// Version     : v0.666
// Copyright   : SatanicWorks
// Description : Solitario en versión consola
//============================================================================

#include <iostream>
#include "Deck.h"
#include "Game.h"
using namespace std;

// PRE:  --
// POST: sem > 0
void readSteps(int &seed) {

	do
	{
		cout << "ENTRA UNA LLAVOR POSITIVA: ";
		cin  >> seed;

	} while (seed <= 0);
}

// PRE:  --
// POST: open == 1 || open == 2
void openCards(int &open) {

	do {

		cout << "QUANTES CARTES VOLS OBRIR?" << endl;
		cout << "1.- D'UNA EN UNA"           << endl;
		cout << "2.- DE TRES EN TRES"        << endl;
		cin  >> open;

	} while (!(open > 0 && open < 3));

	if (open == 2) open = 3;
}

// PRE:  --
// POST: --
void menu(const int &open) {

	cout << "MENU" << endl;

	if (open == 1)
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


// DESCRIPTION: Lee una plantSeed de value positivo, immediatamente pide
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

	int seed;
	int open;

	readSteps(seed);
	openCards(open);

	Deck mainDeck(seed);

	Game mainGame(mainDeck, open);

	cout << mainGame << endl;
	menu(open);

	int option;
	cout << "OPTION: ";
	cin  >> option;

	while (option != 0 && !mainGame.isFinished()) {

		if      (option == 1) mainGame.openCard();
		else if (option == 2) mainGame.hand2board();
		else if (option == 3) mainGame.hand2club();
		else if (option == 4) mainGame.withinBoard();
		else if (option == 5) mainGame.board2club();
		else if (option == 6) mainGame.club2board();
		else if (option == 9) menu(open);
		else {

			cout << "OPTION NO DEFINIDA " << option << endl;
			menu(open);
		}

		if (option != 9) cout << mainGame << endl;

		if (!mainGame.isFinished()) {

			cout << "OPTION: ";
			cin  >> option;
		}
	}

	if (!mainGame.isFinished())
		cout << "PARTIDA ABANDONADA" << endl;
	else {
		cout << "PARTIDA GUANYADA AMB " << mainGame.getMoves()    << " JUGADES";
		cout << " AMB UN TOTAL DE "     << mainGame.getScore() << " PUNTS" << endl;
	}

	return 0;
}
