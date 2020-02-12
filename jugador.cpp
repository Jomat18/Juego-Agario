
#include "Jugador.h"
#include <sstream>
#include <iomanip>
#include <GL/glut.h>

using namespace std;

Jugador::Jugador(int radio):Celula(radio){
	vidas = rand() % 4 + 3;
	n_comidos = 0;
	key = 0;
}

void Jugador::dibujar_masa()
{
	string masa;
	std::ostringstream oss;
	oss << radio_masa;
	masa.append(oss.str());
	int len = masa.size();
	glRasterPos2i(x - 10, y - 5);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, masa[i]);

}

void Jugador::movimiento()
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (x > radio_masa)
			x -= velocidad;
		break;
	case GLUT_KEY_RIGHT:
		if (x < ancho - radio_masa)
			x += velocidad;
		break;
	case GLUT_KEY_DOWN:
		if (y > radio_masa)
			y -= velocidad;
		break;
	case GLUT_KEY_UP:
		if (y < alto - radio_masa)
			y += velocidad;
		break;

	}
	glutPostRedisplay();
}

void Jugador::modificar_velocidad() {

	if (velocidad > 0)
		velocidad -= radio_masa * (0.008);

	std::cout << velocidad << std::endl;
}


void Jugador::comido() {
	--vidas;
}

void Jugador::multiplicarse()
{

}

