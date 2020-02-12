#ifndef CELULA_MAYOR_H
#define CELULA_MAYOR_H
#include "Celula.h"

class Celula_mayor : public Celula {
public:
	int n_comidos;
public:
	Celula_mayor(int radio);
	void dibujar_masa();
	void movimiento();
	void modificar_velocidad();
};

#endif
