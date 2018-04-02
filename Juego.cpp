/*
 * Juego.cpp
 *
 *  Created on: 11 de jun. de 2016
 *      Author: evilchuck
 */

#include "Juego.h"

const int Juego::_PUNT[5] = { 2, 5, 10, 15, 25 };

const string Juego::_MEN_MOV[11] = {
		"A QUINA COLUMNA LA VOLS POSAR: ", "LA CARTA NO ES POT POSAR A LA COLUMNA ",
		"NO HI HA CAP CARTA PER AGAFAR", "NO ES POT APILAR LA CARTA",
		"ENTRA LA COLUMNA ORIGEN I LA FILA ORIGEN: ", "ENTRA LA COLUMNA DESTI: ",
		"LA CARTA NO ES POT MOURE", "ENTRA LA COLUMNA ORIGEN: ",
		"LA CARTA NO ES POT APILAR", "ENTRA LA PILA: ",
		"A LA PILA NO HI HA CAP CARTA PER RECUPERAR"
};

const string Juego::_MEN_JUG[9] = {
		"ESTAT DEL JOC", "JOC EN CURS", " - J:", " P:[", "]",
		" M:[", "]", "JOC ACABAT", "CARTES DESCARTADES: "
};


Juego::Juego() {

	a_nJugadas   = 0;
	a_puntuacion = 0;
	a_abNCartas  = 1;
}

Juego::Juego(const Baraja &bar, const int &abrir) {

	a_nJugadas   = 0;
	a_puntuacion = 0;
	a_abNCartas  = abrir;

	int cols = _COLS;
	a_tablero = Tablero(bar, cols);

	int max = _MAX_CARTAS - a_tablero.nCartas();

	for (int i = 0; i < max; i++) {

		Carta tmp = bar.getCarta(_MAX_CARTAS - 1 - i);

		a_manos[0].apilar(tmp);
	}
}

void Juego::abrirCarta() {

	a_ultimasCartas = "";

	if (!a_manos[0].vacio()) {

		int nCartas = 0;

		while (!a_manos[0].vacio() && nCartas < a_abNCartas) {

			Carta tmp = a_manos[0].cima();
			tmp.voltear();

			a_ultimasCartas += tmp.toString();
			a_ultimasCartas += " ";

			a_manos[1].apilar(tmp);
			a_manos[0].retirar();

			nCartas++;
		}
		a_nJugadas++;
		if (a_nJugadas % 10 == 0) a_puntuacion -= _PUNT[0];

	} else {

		if (!a_manos[1].vacio()) {

			a_manos[0].copInv(a_manos[1]);
			a_manos[1].liberar();
			a_nJugadas++;

			if (a_abNCartas == 1) a_puntuacion -= _PUNT[4];
			else                  a_puntuacion -= _PUNT[2];

			if (a_nJugadas % 10 == 0) a_puntuacion -= _PUNT[0];
		}
	}
}

void Juego::manTablero() {

	if (a_manos[1].vacio())
		cout << _MEN_MOV[2] << endl;
	else {

		int colD;
		cout << _MEN_MOV[0];
		cin  >> colD;
		colD--;

		if (colD < 0 || colD > a_tablero.maxCol())
			cout << _MEN_MOV[1] << (colD + 1) << endl;
		else {

			Carta dest = a_manos[1].cima();

			if (!a_tablero.colCarta(dest, colD))
				cout << _MEN_MOV[1] << (colD + 1) << endl;
			else {
				a_manos[1].retirar();
				a_nJugadas++;
				a_puntuacion += _PUNT[1];

				if (a_nJugadas % 10 == 0) a_puntuacion -= _PUNT[0];
			}
		}
	}
}

void Juego::manoAlPalo() {

	if (a_manos[1].vacio())
		cout << _MEN_MOV[2] << endl;
	else {

		Carta desc = a_manos[1].cima();
		int cima = desc.getPalo();

		if (a_palos[cima].vacio()) {

			if (desc.getNumero() != 0)
				cout << _MEN_MOV[3] << endl;
			else {

				a_palos[cima].apilar(desc);
				a_manos[1].retirar();
				a_nJugadas++;
				a_puntuacion += _PUNT[2];

				if (a_nJugadas % 10 == 0) a_puntuacion -= _PUNT[0];
			}
		} else {

			Carta cimPalo = a_palos[cima].cima();

			if (desc > cimPalo) {

				a_palos[cima].apilar(desc);
				a_manos[1].retirar();
				a_nJugadas++;
				a_puntuacion += _PUNT[2];

				if (a_nJugadas % 10 == 0) a_puntuacion -= _PUNT[0];

			} else
				cout << _MEN_MOV[3] << endl;
		}
	}
}

void Juego::tablAlTabl() {

	int colO, filaO;
	cout << _MEN_MOV[4];
	cin  >> colO >> filaO;
	colO--; filaO--;

	if (colO  < 0 || colO  > a_tablero.maxCol() ||
		filaO < 0 || filaO > a_tablero.getLongitud(colO)) {

			cout << _MEN_MOV[6] << endl;

	} else {

		bool posValid = a_tablero.getLongitud(colO) > filaO;
		bool visible  = a_tablero.getCarta(colO, filaO).visible();

		if (!visible || !posValid)
			cout << _MEN_MOV[6] << endl;
		else {

			int colD;
			cout << _MEN_MOV[5];
			cin  >> colD;
			colD--;

			if (colD < 0 || colD > a_tablero.maxCol())
				cout << _MEN_MOV[1] << (colD + 1) << endl;
			else {

				bool volteado = false;

				if (!a_tablero.movCarta(colO, filaO, colD, volteado))
					cout << _MEN_MOV[1] << (colD + 1) << endl;
				else {

					a_nJugadas++;
					if (volteado) a_puntuacion += _PUNT[1];

					if (a_nJugadas % 10 == 0) a_puntuacion -= _PUNT[0];
				}
			}
		}
	}
}

void Juego::tablAlPalo() {

	int colO;
	cout << _MEN_MOV[7];
	cin  >> colO;
	colO--;

	if (colO < 0 || colO > a_tablero.maxCol())
		cout << _MEN_MOV[2] << endl;
	else {

		bool volteado = false;

		int filaO = (a_tablero.getLongitud(colO) - 1);

		Carta palo = a_tablero.getCarta(colO, filaO);

		if (a_palos[palo.getPalo()].vacio()) {

			if (palo.getNumero() != 0)
				cout << _MEN_MOV[8] << endl;
			else {

				a_tablero.retCarta(colO, volteado);
				a_palos[palo.getPalo()].apilar(palo);
				a_nJugadas++;
				a_puntuacion += _PUNT[2];

				if (a_nJugadas % 10 == 0) a_puntuacion -= _PUNT[0];
			}
		} else {

			if (palo > a_palos[palo.getPalo()].cima()) {

				a_tablero.retCarta(colO, volteado);
				a_palos[palo.getPalo()].apilar(palo);
				a_nJugadas++;
				a_puntuacion += _PUNT[2];

				if (a_nJugadas % 10 == 0) a_puntuacion -= _PUNT[0];

			} else
				cout << _MEN_MOV[8] << endl;
		}
		if (volteado) a_puntuacion += _PUNT[1];
	}
}

void Juego::paloAlTabl() {

	int palo;
	cout << _MEN_MOV[9];
	cin  >> palo;
	palo--;

	if (palo < 0 || palo >= _PALOS)
		cout << _MEN_MOV[10] << endl;
	else {

		if (a_palos[palo].vacio())
			cout << _MEN_MOV[10] << endl;
		else {

			Carta mov = a_palos[palo].cima();

			int colD;
			cout << _MEN_MOV[0];
			cin  >> colD;
			colD--;

			if (colD < 0 || colD > a_tablero.maxCol())
				cout << _MEN_MOV[1] << (colD + 1) << endl;
			else {

				if (!a_tablero.colCarta(mov, colD))
					cout << _MEN_MOV[1] << (colD + 1) << endl;
				else {
					a_palos[palo].retirar();
					a_nJugadas++;
					a_puntuacion -= _PUNT[3];

					if (a_nJugadas % 10 == 0) a_puntuacion -= _PUNT[0];
				}
			}
		}
	}
}

bool Juego::acabado() const {

	bool acabado = 	a_palos[0].largo() == 13 &&
					a_palos[1].largo() == 13 &&
					a_palos[2].largo() == 13 &&
					a_palos[3].largo() == 13;

	return acabado;
}

int Juego::getJugadas() const {
	return a_nJugadas;
}

int Juego::getPuntuacion() const {
	return a_puntuacion;
}

ostream &operator<<(ostream &o, const Juego &j) {

	o << endl << j._MEN_JUG[0] << endl;

	o << j._MEN_JUG[8] << j.a_ultimasCartas << endl;

	for (int i = 0; i < j._PALOS; i++)
		o << j.a_palos[i];

	o << "   ";

	for (int i = 0; i < j._MANOS; i++)
		o << j.a_manos[i];

	o << endl << j.a_tablero << endl;

	if (!j.acabado()) {

		o << j._MEN_JUG[1] << j._MEN_JUG[2] << j.getJugadas() << j._MEN_JUG[3];
		o << j.a_palos[0].largo() << j._SEP << j.a_palos[1].largo() << j._SEP;
		o << j.a_palos[2].largo() << j._SEP << j.a_palos[3].largo();
		o << j._MEN_JUG[4] << j._MEN_JUG[5];
		o << j.a_manos[0].largo() << j._SEP << j.a_manos[1].largo();
		o << j._MEN_JUG[6] << " " << j.getPuntuacion() << " PUNTS" << endl;

	} else
		o << j._MEN_JUG[7] << endl;

	return o;
}
