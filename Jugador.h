#ifndef JUGADOR_H
#define JUGADOR_H
#include "Celula.h"
#include <iostream>

class Jugador : public Celula {
public:
	int vidas;
	int n_comidos;
	int key;
public:
	Jugador(int radio);
	void dibujar_masa();
	void movimiento();
	void modificar_velocidad();
	void comido();
	void multiplicarse();
	
};

#endif
