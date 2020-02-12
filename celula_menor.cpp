
#include "Celula_menor.h"

Celula_menor::Celula_menor(int radio) :Celula(radio) {}

void Celula_menor::movimiento() {

	if (y <= radio_masa)
		mov_y = mov_y*(-1);

	if (x >= ancho - radio_masa)
		mov_x = mov_x*(-1);

	if (x <= radio_masa)
		mov_x = mov_x*(-1);

	if (y >= alto - radio_masa)
		mov_y = mov_y*(-1);

	y += mov_y;
	x += mov_x;

}
