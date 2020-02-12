
#include "Virus.h"

Virus::Virus(int r, int g, int b, int radio) :Celula(r, g, b, radio) {}

void Virus::movimiento() {

	if (y <= radio_masa)
		mov_y = mov_y * (-1);

	if (x >= ancho - radio_masa)
		mov_x = mov_x * (-1);

	if (x <= radio_masa)
		mov_x = mov_x * (-1);

	if (y >= alto - radio_masa)
		mov_y = mov_y * (-1);

	y += mov_y;
	x += mov_x;

}
