
#include "Juego.h"
#include <time.h>       
#include <sstream>
#include <iomanip>
#include <math.h>

const int masa_mayor = 20, masa_menor = 8, masa_virus = 5, masa_jugador = 15;
const int crecer = 5;
clock_t start; //Es el tiempo desde que se inicia el juego
double tiempo;	//guarda el calculo del tiempo en cada instante
double minutos = 2;  //3 minutos decrece 2:59
double segundos = 60;
const int n_pedazos = 4;
bool regresar = true;

using namespace std;

Juego::Juego()
{
	virus_activado=false;
	srand(time(NULL));
	n_celulas_mayores = rand() % 15 + 5;   
	n_celulas_menores = rand() % 20 + 10;
	n_virus = rand() % 10 + 5;
	total = n_celulas_mayores + n_celulas_menores + n_virus;
	nivel = 1;
	jugador = new Jugador(masa_jugador);

	for (int i = 0; i < n_celulas_mayores; i++)
	{
		Celula_mayor *nuevo = new Celula_mayor(masa_mayor);
		c_mayores.push_back(*nuevo);
	}

	for (int i = 0; i < n_celulas_menores; i++)
	{
		Celula_menor *nuevo = new Celula_menor(masa_menor);
		c_menores.push_back(*nuevo);
	}

	for (int i = 0; i < n_virus; i++)
	{
		Virus *nuevo = new Virus(0, 1, 0, masa_virus);
		c_virus.push_back(*nuevo);
	}
}

Juego::~Juego()
{
	delete jugador;
}

void Juego::init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPointSize(4.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, ancho, 0.0, alto);
}

void Juego::Timer(int valor)
{
	glutTimerFunc(3000 / 60, Timer, valor);  //velocidad de movimiento
	glutPostRedisplay();
}

void Juego::iniciar(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(ancho, alto);
	glutCreateWindow("Agario");
	init();
	Timer(0);
}

void Juego::mostrar_tiempo()
{
	string tiempo_texto = "Tiempo: "; 
	std::ostringstream oss;
	oss << minutos;
	oss << " : ";

	tiempo = 60 - (clock() - start) / (double)CLOCKS_PER_SEC;
	if (tiempo <= 0)
	{
		start = clock();
		minutos--;
	}

	oss << std::setprecision(4) << tiempo;
	tiempo_texto.append(oss.str());
	int len = tiempo_texto.size();
	glRasterPos2i(20, alto - 50);

	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tiempo_texto[i]);
	
}

void Juego::siguiente_nivel()
{	
	if (jugador && nivel<4 && jugador->n_comidos > round(total / 2))
	{
		init();
		virus_activado = false;
		c_mayores.clear();
		c_menores.clear();
		c_virus.clear();

		nivel++;
		int aumento = 2;
		n_celulas_mayores += (nivel - 1)*aumento;
		for (int i = 1; i < nivel; i++)
			n_celulas_menores += (n_celulas_menores / 2);

		n_virus = rand() % 4 + 3;
		total = n_celulas_mayores + n_celulas_menores + n_virus;

		jugador->radio_masa = masa_jugador;
		jugador->x = rand() % (ancho - 2 * jugador->radio_masa) + jugador->radio_masa;
		jugador->y = rand() % (alto - 2 * jugador->radio_masa) + jugador->radio_masa;
		jugador->velocidad = 15;
		jugador->vidas = rand() % 4 + 3;
		jugador->n_comidos = 0;

		for (int i = 0; i < n_celulas_mayores; i++)
		{
			Celula_mayor *nuevo = new Celula_mayor(masa_mayor);
			c_mayores.push_back(*nuevo);
		}

		for (int i = 0; i < n_celulas_menores; i++)
		{
			Celula_menor *nuevo = new Celula_menor(masa_menor);
			c_menores.push_back(*nuevo);
		}

		for (int i = 0; i < n_virus; i++)
		{
			Virus *nuevo = new Virus(0, 1, 0, masa_virus);
			c_virus.push_back(*nuevo);
		}
	}
}

void Juego::juego_terminado()
{
	if (jugador && nivel ==4 && jugador->n_comidos > round(total / 2))  //
	{
		cout << "Ganador" << endl;
		exit(0);
	}

	if (jugador && jugador->vidas == 0)
	{
		Jugador *p = jugador;
		jugador = 0;
		delete p;
		//exit(0);
	}

	if(minutos == 0)
		exit(0);
}

void Juego::virus_multiplicarse()
{
	for (int i = 0; !virus_activado && i < n_virus*(n_pedazos - 1); i++)
	{
		Virus *nuevo = new Virus(0, 1, 0, masa_virus);
		c_virus.push_back(*nuevo);
	}
	virus_activado = true;
}

void Juego::colision()
{
	double r_x, r_y, d, veinte_porc;
	for (int i = 0; i < c_mayores.size(); i++)
	{
		for (int j = i + 1; i < c_mayores.size() && j < c_mayores.size(); j++)
		{
			r_x = pow(c_mayores[i].x - c_mayores[j].x, 2);
			r_y = pow(c_mayores[i].y - c_mayores[j].y, 2);
			d = sqrt(r_x + r_y);

			if (d <= c_mayores[i].radio_masa + c_mayores[j].radio_masa)
			{
				veinte_porc = c_mayores[j].radio_masa*(0.2);
				if (c_mayores[j].radio_masa + veinte_porc < c_mayores[i].radio_masa)
				{
					c_mayores.erase(c_mayores.begin() + j);
					c_mayores[i].radio_masa += crecer;
					c_mayores[i].modificar_velocidad();
					c_mayores[i].n_comidos++;
					j--;
				}

				else
				{
					veinte_porc = c_mayores[i].radio_masa*(0.2);
					if (c_mayores[i].radio_masa + veinte_porc < c_mayores[j].radio_masa)
					{
						c_mayores.erase(c_mayores.begin() + i);
						c_mayores[j].radio_masa += crecer;
						c_mayores[j].modificar_velocidad();
						c_mayores[j].n_comidos++;
						j--;
					}
				}

			}

		}
	}

	for (int i = 0; i < c_mayores.size(); i++)
	{
		for (int j = 0; i < c_mayores.size() && j < c_menores.size(); j++)
		{
			r_x = pow(c_mayores[i].x - c_menores[j].x, 2);
			r_y = pow(c_mayores[i].y - c_menores[j].y, 2);
			d = sqrt(r_x + r_y);

			if (d <= c_mayores[i].radio_masa + c_menores[j].radio_masa)
			{
				veinte_porc = c_menores[j].radio_masa*(0.2);
				if (c_menores[j].radio_masa + veinte_porc < c_mayores[i].radio_masa)
				{
					c_menores.erase(c_menores.begin() + j);
					c_mayores[i].radio_masa += crecer;
					c_mayores[i].modificar_velocidad();
					c_mayores[i].n_comidos++;
					j--;
				}
			}

		}
	}

	for (int i = 0; virus_activado && i < c_mayores.size(); i++)
	{
		for (int j = 0; i < c_mayores.size() && j < c_virus.size(); j++)
		{
			r_x = pow(c_mayores[i].x - c_virus[j].x, 2);
			r_y = pow(c_mayores[i].y - c_virus[j].y, 2);
			d = sqrt(r_x + r_y);

			if (d <= c_mayores[i].radio_masa + c_virus[j].radio_masa)
			{
				c_mayores.erase(c_mayores.begin() + i);
				c_virus.erase(c_virus.begin() + j);
				i--;
				j--;
			}
		}
	}

	for (int i = 0; i < c_mayores.size(); i++)
	{
		if (jugador)
		{
			r_x = pow(c_mayores[i].x - jugador->x, 2);
			r_y = pow(c_mayores[i].y - jugador->y, 2);
			d = sqrt(r_x + r_y);

			if (d <= c_mayores[i].radio_masa + jugador->radio_masa)
			{
				veinte_porc = jugador->radio_masa*(0.2);
				if (jugador->radio_masa + veinte_porc < c_mayores[i].radio_masa)
				{
					jugador->radio_masa = masa_jugador;
					jugador->x = rand() % (ancho - 2 * jugador->radio_masa) + jugador->radio_masa;
					jugador->y = rand() % (alto - 2 * jugador->radio_masa) + jugador->radio_masa;
					jugador->velocidad = 15;
					jugador->comido();
					c_mayores[i].radio_masa += crecer;
					c_mayores[i].modificar_velocidad();
					c_mayores[i].n_comidos++;
				}

				else
				{
					veinte_porc = c_mayores[i].radio_masa*(0.2);
					if (c_mayores[i].radio_masa + veinte_porc < jugador->radio_masa)
					{
						c_mayores.erase(c_mayores.begin() + i);
						i--;
						jugador->radio_masa += crecer;
						jugador->modificar_velocidad();
						jugador->n_comidos++;
					}
				}
			}
		}
	}

	if (jugador && c_menores.size())
	{
		for (int j = 0; j < c_menores.size(); j++)
		{
			r_x = pow(jugador->x - c_menores[j].x, 2);
			r_y = pow(jugador->y - c_menores[j].y, 2);
			d = sqrt(r_x + r_y);

			if (d <= jugador->radio_masa + c_menores[j].radio_masa)
			{
				veinte_porc = c_menores[j].radio_masa*(0.2);
				if (c_menores[j].radio_masa + veinte_porc < jugador->radio_masa)
				{
					c_menores.erase(c_menores.begin() + j);
					j--;
					jugador->radio_masa += crecer;
					jugador->modificar_velocidad();
					jugador->n_comidos++;
				}
			}
		}

		for (int j = 0; jugador && virus_activado && j < c_virus.size(); j++)
		{
			r_x = pow(jugador->x - c_virus[j].x, 2);
			r_y = pow(jugador->y - c_virus[j].y, 2);
			d = sqrt(r_x + r_y);

			if (d <= jugador->radio_masa + c_virus[j].radio_masa)
			{
				jugador->radio_masa = masa_jugador;
				jugador->x = rand() % (ancho - 2 * jugador->radio_masa) + jugador->radio_masa;
				jugador->y = rand() % (alto - 2 * jugador->radio_masa) + jugador->radio_masa;
				jugador->velocidad = 15;
				jugador->comido();
				c_virus.erase(c_virus.begin() + j);
				j--;
			}

		}

	}

}
