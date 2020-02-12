#ifndef CELULA_H
#define CELULA_H

#define ancho 1248	//dimensiones de la ventana de juego
#define alto 600	//dimensiones de la ventana de juego

class Celula {
public:
	float x, y;	//Posicion de la celula
	int radio_masa;		//radio y tambien la masa de la celula
	double color3[3];  //Color de la celula
	float velocidad;
	float mov_x, mov_y; //movimiento en x y y

public:
	Celula(int radio);
	Celula(int r, int g, int b, int radio);  //constructor para el virus
	void dibujarCelula();
	virtual void modificar_velocidad();
	virtual void movimiento()=0;		
};


#endif