
#include "Celula.h"
#include <stdlib.h>    //libreria para usar la funcion rand()
#include <GL/glut.h>
#include <math.h> 
#include <iostream>

int direccion[2] = { -2, 2};	//sentido de movimiento de la celula

Celula::Celula(int radio) {
	radio_masa = radio;
	color3[0] = rand() % 255;
	color3[1] = rand() % 255;
	color3[2] = rand() % 255;
	x = rand() % (ancho - 2 * radio_masa) + radio_masa;
	y = rand() % (alto - 2 * radio_masa) + radio_masa;
	velocidad = 15;
	mov_x = direccion[rand() % 2];
	mov_y = direccion[rand() % 2];

}

Celula::Celula(int r, int g, int b, int radio) {
	radio_masa = radio;
	color3[0] = r;
	color3[1] = g;
	color3[2] = b;
	x = rand() % (ancho - 2 * radio_masa) + radio_masa;
	y = rand() % (alto - 2 * radio_masa) + radio_masa;
	velocidad = 15;
	mov_x = direccion[rand() % 2];
	mov_y = direccion[rand() % 2];
}

void Celula::dibujarCelula() {
	int triangulos = 100;

	float twicePi = 2.0f * 3.14159;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= triangulos; i++) {
		glVertex2f(
			x + (radio_masa * cos(i *  twicePi / triangulos)),
			y + (radio_masa * sin(i * twicePi / triangulos))
		);
	}
	glEnd();
}


void Celula::modificar_velocidad() {
	/*
	
	*/
}

