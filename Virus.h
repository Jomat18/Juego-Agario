#ifndef VIRUS_H
#define VIRUS_H
#include "Celula.h"

class Virus : public Celula {
public:
	Virus(int r, int g, int b, int radio);
	void movimiento();

};

#endif
