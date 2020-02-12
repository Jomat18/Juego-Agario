#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include "Celula_mayor.h"
#include "Celula_menor.h"
#include "Virus.h"
#include <GL/glut.h>
#include <vector>

using namespace std;

class Juego {

public:
	int n_celulas_mayores;
	int n_celulas_menores;
	int n_virus;
	float total;
	int nivel;
	bool virus_activado;
	Jugador *jugador;
	vector<Celula_mayor> c_mayores;
	vector<Celula_menor> c_menores;
	vector<Virus> c_virus;

public:

	Juego();
	~Juego();
	void init();
	static void Timer(int value);
	void iniciar(int argc, char** argv);
	void mostrar_tiempo();
	void juego_terminado();
	void colision();
	void siguiente_nivel();
	void virus_multiplicarse();

};

#endif
