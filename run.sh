#!/bin/sh

g++ -g -Wall -c celula.cpp #-lGL -lGLU -lglut
g++ -g -Wall -c celula_mayor.cpp #-lGL -lGLU -lglut
g++ -g -Wall -c celula_menor.cpp #-lGL -lGLU -lglut
g++ -g -Wall -c juego.cpp #-lGL -lGLU -lglut
g++ -g -Wall -c jugador.cpp #-lGL -lGLU -lglut
g++ -g -Wall -c virus.cpp #-lGL -lGLU -lglut
g++ -g -Wall -c main.cpp #-lGL -lGLU -lglut
g++ main.o celula.o celula_mayor.o celula_menor.o juego.o jugador.o virus.o -o gl -lGL -lGLU -lglut 
./gl
