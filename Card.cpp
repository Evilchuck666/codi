/*
* Card.cpp
*
*  Created on: 10 de jun. de 2016
*      Author: EvilChuck
*/

#include "Card.h"

const char Card::_CLUBS[_N_CLUBS] = {'P', 'c', 'd', 'T'};
const char Card::_NUMBERS[_N_NUMBERS] = {'A', '2', '3', '4', '5',
                                         '6', '7', '8', '9', 'D',
                                         'J', 'Q', 'K'};

Card::Card() : Card(0, 0) {}

Card::Card(const int &p, const int &n) {

    m_club = p;
    m_number = n;
    m_visible = false;
    m_colour = m_club % _CH_COL != 0;
}

Card::Card(const Card &c) {
    *this = c;
}


int Card::getClub() const {
    return m_club;
}

int Card::getNumber() const {
    return m_number;
}

bool Card::isVisible() const {
    return m_visible;
}

string Card::toString() const {

    string str = "";

    if (m_visible) {

        str += _NUMBERS[m_number];
        str += _CLUBS[m_club];

    } else str += "**";

    return str;
}


void Card::turn() {
    m_visible = !m_visible;
}


bool Card::operator<(const Card &c) const {
    return m_colour != c.m_colour && m_number == (c.m_number - 1);
}

bool Card::operator>(const Card &c) const {
    return m_club == c.m_club && m_number == (c.m_number + 1);
}

Card &Card::operator=(const Card &c) {

    if (this != &c) {

        m_club = c.m_club;
        m_number = c.m_number;
        m_visible = c.m_visible;
        m_colour = c.m_colour;
    }
    return *this;
}
