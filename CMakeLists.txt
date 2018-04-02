cmake_minimum_required(VERSION 3.10)
project(codi)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Deck.cpp
        Deck.h
        Card.cpp
        Card.h
        Game.cpp
        Game.h
        main.cpp
        Stack.cpp
        Stack.h
        Board.cpp
        Board.h)

include_directories(.)

add_executable(codi ${SOURCE_FILES})
