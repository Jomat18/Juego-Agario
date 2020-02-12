
#include "Celula_mayor.h"
#include <sstream>
#include <iomanip>
#include <GL/glut.h>
#include <iostream>

using namespace std;

Celula_mayor::Celula_mayor(int radio) :Celula(radio) {
	n_comidos=0;
}

void Celula_mayor::dibujar_masa()
{
	string masa;
	std::ostringstream oss;
	oss << radio_masa;
	masa.append(oss.str());
	int len = masa.size();
	glRasterPos2i(x - 10 - mov_x, y - 5 - mov_y);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, masa[i]);

}

void Celula_mayor::movimiento() {

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
	//std::cout << x << " " << y << endl;

}

void Celula_mayor::modificar_velocidad() {
	
	if (mov_x > 0)
		mov_x -= radio_masa * (0.0008);
	else
		mov_x += radio_masa * (0.0008);

	if(mov_y > 0)
		mov_y -= radio_masa * (0.0008);
	else	
		mov_y += radio_masa * (0.0008);
}

