
#include "Juego.h"
#include <math.h>

//Funcion Opengl
void display();
void keyboard(int key, int x, int y);
void Key_virus(unsigned char key, int x, int y);

Juego *juego = new Juego();

int main(int argc, char** argv) {
	juego->iniciar(argc,argv);
	glutSpecialFunc(keyboard);
	glutKeyboardFunc(Key_virus);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void display() {

	juego->siguiente_nivel();
	juego->colision();
	juego->juego_terminado();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	juego->mostrar_tiempo();

	if (juego->jugador)
	{
		glColor3ub(juego->jugador->color3[0], juego->jugador->color3[1], juego->jugador->color3[2]);
		juego->jugador->dibujarCelula();
		glColor3f(0, 0, 0);
		juego->jugador->dibujar_masa();
	}

	for(int i = 0; i < juego->c_mayores.size(); i++)
	{
		glColor3ub(juego->c_mayores[i].color3[0], juego->c_mayores[i].color3[1], juego->c_mayores[i].color3[2]);
		juego->c_mayores[i].dibujarCelula();
		juego->c_mayores[i].movimiento();
		glColor3f(0, 0, 0);
		juego->c_mayores[i].dibujar_masa();
	}

	for (int i = 0; i < juego->c_menores.size(); i++)
	{
		glColor3ub(juego->c_menores[i].color3[0], juego->c_menores[i].color3[1], juego->c_menores[i].color3[2]);
		juego->c_menores[i].dibujarCelula();
		juego->c_menores[i].movimiento();
	}

	for (int i = 0; i < juego->c_virus.size(); i++)
	{
		glColor3ub(juego->c_virus[i].color3[0], juego->c_virus[i].color3[1], juego->c_virus[i].color3[2]);
		juego->c_virus[i].dibujarCelula();
		juego->c_virus[i].movimiento();
	}

	glFlush();
}

void keyboard(int key, int x, int y)
{   
	if (juego->jugador)
	{
		juego->jugador->key = key;
		juego->jugador->movimiento();
	}
}

void Key_virus(unsigned char key, int x, int y)
{
	if(key=='x')
		juego->virus_multiplicarse();

}
