cmake_minimum_required(VERSION 3.10)
project(codi)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(codi
        Baraja.cpp
        Baraja.h
        Carta.cpp
        Carta.h
        Juego.cpp
        Juego.h
        main.cpp
        Pila.cpp
        Pila.h
        Tablero.cpp
        Tablero.h)
