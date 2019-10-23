#include <stdlib.h>
#include "GL/glut.h"
#include <iostream>
#include <cstdlib>
#include <time.h>  
#pragma comment(lib, "glut32.lib")
#define WINDOW_TITLE "Project"
using namespace std;

double pi = 3.14159265359; //pi, es usado para dibujar los circulos
double ng = pi / 2; //Noventa grados
//Basado en cuentas de que dentro de cada cuadrado deberia de haber un 
double radio = 75 / sqrt(2); //Radio de los segmentos de circulos
double theta = 1.2309594173407746821; //Mitad del angulo que se forma entre el centro y las dos esquinas del segmento
int x_value = -450; //Esta variable se usa para varios movimientos sobre x
int y_value = 350; //Esta variable se usa para varios movimientos sobre y
int ang = 0; //Esta variable se usa para varios rotaciones
int fase = 0;  //Se usa para determinar en que parte del programa esta
int ang2 = 0; //Esta variable se usa para varias rotaciones
int vueltas = 0; //Se usa para determinar en que parte del programa esta
int movida = 0; //Se usa para determinar en que parte del programa esta
int cantMov = 5; //Se usa para determinar el ritmo de movimiento
int cantRot = 5; //Se usa para determinar el ritmo de rotacion
double crecimiento = 0.5;
bool flag1 = true;
bool flag2 = true;
int frame = 0;

void init(void) {
	glClearColor(.5, .5, .5, 0.0);
	glMatrixMode(GL_PROJECTION); //
	gluOrtho2D(-450.0, 450.0, -350.0, 350.0); //Coordenadas de visualización 
}

void eligeColor(int color) {
	switch (color)
	{
	case 1:
		glColor3f(0, 0, 0);//Negro
		break;
	case 2:
		glColor3f(1, 1, 1);//Blanco
		break;
	case 3:
		glColor3f(1, 0.2705, 0);//Naranja
		break;
	default:
		break;
	}
}

void cuadrado(double x, double y, int color) {
	glBegin(GL_POLYGON);
	eligeColor(color);
	glVertex3f(x, y, 0);
	glVertex3f(x - 100, y, 0);
	glVertex3f(x - 100, y - 100, 0);
	glVertex3f(x, y - 100, 0);
	glEnd();

}

void segmentoCirculo(double thetaIni, double thetaFin, double cx, double cy) {
	//Esta funcion deberia de incluir el radio en la llamada, pero siempre es el mismo
	for (double a = thetaIni; a <= thetaFin; a += (pi / 200)) {
		glVertex3f(cx + radio * cos(a), cy + radio * sin(a), 0);
	}
}

void circulo(double x, double y, int r) {
	glBegin(GL_POLYGON);
	switch (r)
	{
	case 1: //Viendo abajo
		glVertex3f(x, y - 50, 0);
		segmentoCirculo(ng - theta, ng + theta, x - 50, y - 50 - (radio / 3));
		glVertex3f(x - 100, y - 50, 0);
		break;
	case 2: //Viendo arriba
		glVertex3f(x - 100, y, 0);
		segmentoCirculo(3 * ng - theta, 3 * ng + theta, x - 50, y + (radio / 3));
		glVertex3f(x, y, 0);
		break;
	case 3://viendo izquierda
		glVertex3f(x - 50, y - 100, 0);
		segmentoCirculo(4 * ng - theta, 4 * ng + theta, x - 50 - (radio / 3), y - 50);
		glVertex3f(x - 50, y, 0);
		break;
	case 4: //viendo derecha
		glVertex3f(x, y, 0);
		segmentoCirculo(2 * ng - theta, 2 * ng + theta, x + (radio / 3), y - 50);
		glVertex3f(x, y - 100, 0);
		break;
	default:
		break;
	}
	glEnd();
}

void miniCuadro(double x, double y, int colorCua, int colorCir, int rotacion1, int rotacion2) {
	eligeColor(colorCua);
	cuadrado(x, y, colorCua);

	eligeColor(colorCir);
	if (rotacion1 <= 2) {
		circulo(x, y, rotacion1);
		circulo(x, y - 50, rotacion2);
	}
	else {
		circulo(x - 50, y, rotacion1);
		circulo(x, y, rotacion2);
	}
}

void update(int value) {

	//glutPostRedisplay(); // Inform GLUT that the display has changed
	if (fase < 4) {//Se arma el cuadro
		switch (fase) {
		case 0: 
			x_value += 4.5;
			y_value -= 3.5;
			if (x_value == 0) {
				x_value = 450;
				y_value = 350;
				fase=1;
			}
			break;
		case 1:
			x_value -= 4.5;
			y_value -= 3.5;
			if (x_value == 0) {
				x_value = 450;
				y_value = -350;
				fase=2;
			}
			break;
		case 2:
			x_value -= 4.5;
			y_value += 3.5;
			if (x_value == 0) {
				x_value = -450;
				y_value = -350;
				fase=3;
			}
			break;
		case 3:
			x_value += 4.5;
			y_value += 3.5;
			if (x_value == 0) {
				x_value = -50;
				y_value = 150;
				fase=4;
			}
			break;
		}
	}
	else if (vueltas < 18) {//Empiezan a girar las piezas
		ang += cantRot;
		if (ang >= 360) {
			ang = 1;
			vueltas += 1;
		}
	}//
	else if(ang<370) {//gira rapido la de el centro
		ang += vueltas;
		ang *= 1.2;
	}
	else if (movida <= 6) {//se reacomodan algunas piesas
		switch (movida){
		case 0:
			if (x_value < 50)
				x_value += cantMov;
			else
				movida = 1;
			break;
		case 1:
			if (y_value > 50)
				y_value -= cantMov;
			else
				movida = 2;
			break;
		case 2:
			if (x_value > -50)
				x_value -= cantMov;
			else
				movida = 3;
			break;
		case 3:
			if (y_value < 150)
				y_value += cantMov;
			else {
				movida = 4;
				x_value = 150;
			}
			break;
		case 4:
			if (x_value > 50)
				x_value -= cantMov;
			else {
				movida = 5;
				x_value = 250;
			}
			break;
		case 5:
			if (x_value > 150)
				x_value -= cantMov;
			else {
				movida = 6;
				x_value = 350;
			}
			break;
		case 6:
			if (x_value > 250)
				x_value -= cantMov;
			else {
				movida = 7;
			}
			break;
		}
	}
	else if (movida == 7) {//aparece la pieza que desaparecio
		crecimiento+=.005;
		if (crecimiento >= 2)
			movida = 8;
	}
	else if (movida == 8) {//Regresa la pieza que escapo
		crecimiento -= .05;
		if (crecimiento < 1) {
			crecimiento = 1;
			movida = 9;
			crecimiento = 1;
			ang2 = 0;
			x_value = 0;
			y_value = 0;
		}
	}
	else if (movida == 9) {//se mueve todo
		if (flag1) {
			ang2 += 5;
			if (ang2 >= 30)
				flag1 = false;
		}
		else {
			ang2-= 5;
			if (ang2 <=-30)
				flag1 = true;
		}
		if (flag2) {
			crecimiento += (rand()%100)/30*.005;
			if (crecimiento >= 1.3)
				flag2 = false;
		}
		else {
			crecimiento -= (rand() % 100) / 30 * 0.005;
			if (crecimiento <= .7)
				flag2 = true;
		}
		frame += 1;
		if (frame >= 100) {
			movida = 10;
		}
	}
	else {//explota
		x_value+=(rand() % 100)/5;
		y_value+=(rand() % 100)/5;
	}
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

void cuadro(void) {
	glClear(GL_COLOR_BUFFER_BIT); //
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (fase < 4) {
		switch (fase) {
		case 0:
			glTranslated(x_value, y_value, 0);
			miniCuadro(-250, 250, 1, 2, 4, 4);
			miniCuadro(-150, 250, 3, 1, 3, 4);
			miniCuadro(-50, 250, 1, 2, 1, 1);
			miniCuadro(-250, 150, 2, 1, 4, 4);
			miniCuadro(-150, 150, 3, 2, 1, 1);
			miniCuadro(-250, 50, 3, 1, 3, 3);
			break;
		case 1:
			miniCuadro(-250, 250, 1, 2, 4, 4);
			miniCuadro(-150, 250, 3, 1, 3, 4);
			miniCuadro(-50, 250, 1, 2, 1, 1);
			miniCuadro(-250, 150, 2, 1, 4, 4);
			miniCuadro(-150, 150, 3, 2, 1, 1);
			miniCuadro(-250, 50, 3, 1, 3, 3);

			glTranslated(x_value, y_value, 0);
			
			miniCuadro(50, 250, 1, 3, 1, 1);
			miniCuadro(150, 250, 2, 3, 1, 2);
			miniCuadro(250, 250, 3, 1, 4, 3);
			miniCuadro(350, 250, 3, 1, 4, 4);
			miniCuadro(150, 150, 1, 3, 3, 3);
			miniCuadro(250, 150, 3, 1, 2, 1);
			miniCuadro(350, 150, 2, 3, 3, 3);
			miniCuadro(250, 50, 1, 2, 3, 4);
			miniCuadro(350, 50, 2, 1, 2, 1);
			miniCuadro(350, -50, 1, 3, 3, 3);
			break;
		case 2:
			miniCuadro(-250, 250, 1, 2, 4, 4);
			miniCuadro(-150, 250, 3, 1, 3, 4);
			miniCuadro(-50, 250, 1, 2, 1, 1);
			miniCuadro(-250, 150, 2, 1, 4, 4);
			miniCuadro(-150, 150, 3, 2, 1, 1);
			miniCuadro(-250, 50, 3, 1, 3, 3);
			miniCuadro(50, 250, 1, 3, 1, 1);
			miniCuadro(150, 250, 2, 3, 1, 2);
			miniCuadro(250, 250, 3, 1, 4, 3);
			miniCuadro(350, 250, 3, 1, 4, 4);
			miniCuadro(150, 150, 1, 3, 3, 3);
			miniCuadro(250, 150, 3, 1, 2, 1);
			miniCuadro(350, 150, 2, 3, 3, 3);
			miniCuadro(250, 50, 1, 2, 3, 4);
			miniCuadro(350, 50, 2, 1, 2, 1);
			miniCuadro(350, -50, 1, 3, 3, 3);


			glTranslated(x_value, y_value, 0);

			miniCuadro(50, 150, 1, 3, 2, 1);
			miniCuadro(50, 50, 2, 1, 3, 3);
			miniCuadro(150, 50, 2, 3, 4, 4);
			miniCuadro(50, -50, 2, 3, 1, 1);
			miniCuadro(150, -50, 3, 1, 2, 2);
			miniCuadro(250, -50, 2, 1, 2, 1);
			miniCuadro(50, -150, 3, 1, 3, 4);
			miniCuadro(150, -150, 3, 2, 3, 3);
			miniCuadro(250, -150, 2, 3, 1, 1);
			miniCuadro(350, -150, 2, 1, 1, 1);
			break;
		case 3:
			miniCuadro(-250, 250, 1, 2, 4, 4);
			miniCuadro(-150, 250, 3, 1, 3, 4);
			miniCuadro(-50, 250, 1, 2, 1, 1);
			miniCuadro(-250, 150, 2, 1, 4, 4);
			miniCuadro(-150, 150, 3, 2, 1, 1);
			miniCuadro(-250, 50, 3, 1, 3, 3);
			miniCuadro(50, 250, 1, 3, 1, 1);
			miniCuadro(150, 250, 2, 3, 1, 2);
			miniCuadro(250, 250, 3, 1, 4, 3);
			miniCuadro(350, 250, 3, 1, 4, 4);
			miniCuadro(150, 150, 1, 3, 3, 3);
			miniCuadro(250, 150, 3, 1, 2, 1);
			miniCuadro(350, 150, 2, 3, 3, 3);
			miniCuadro(250, 50, 1, 2, 3, 4);
			miniCuadro(350, 50, 2, 1, 2, 1);
			miniCuadro(350, -50, 1, 3, 3, 3);
			miniCuadro(50, 150, 1, 3, 2, 1);
			miniCuadro(50, 50, 2, 1, 3, 3);
			miniCuadro(150, 50, 2, 3, 4, 4);
			miniCuadro(50, -50, 2, 3, 1, 1);
			miniCuadro(150, -50, 3, 1, 2, 2);
			miniCuadro(250, -50, 2, 1, 2, 1);
			miniCuadro(50, -150, 3, 1, 3, 4);
			miniCuadro(150, -150, 3, 2, 3, 3);
			miniCuadro(250, -150, 2, 3, 1, 1);
			miniCuadro(350, -150, 2, 1, 1, 1);

			glTranslated(x_value, y_value, 0);

			miniCuadro(-50, 150, 2, 1, 3, 3);
			miniCuadro(-150, 50, 3, 2, 4, 4);
			miniCuadro(-50, 50, 1, 3, 2, 1);
			miniCuadro(-50, -50, 1, 3, 4, 3);
			miniCuadro(-250, -50, 2, 1, 1, 1);
			miniCuadro(-150, -50, 2, 1, 3, 3);
			miniCuadro(-250, -150, 1, 3, 2, 1);
			miniCuadro(-150, -150, 3, 2, 3, 4);
			miniCuadro(-50, -150, 1, 2, 2, 2);
			break;
		}
	}
	else if (ang <= 370) {
		glRotated(ang, 0, 0, 1);
		miniCuadro(50, 50, 2, 1, 3, 3);


		//glFlush();
		glLoadIdentity();
		if (vueltas > 0 && vueltas < 18)
			glRotated(-ang, 0, 0, 1);

		miniCuadro(50, 150, 1, 3, 2, 1);
		miniCuadro(50, -50, 2, 3, 1, 1);
		miniCuadro(-50, 50, 1, 3, 2, 1);
		miniCuadro(150, 50, 2, 3, 4, 4);

		glLoadIdentity();
		if (vueltas > 2 && vueltas < 16)
			glRotated(ang, 0, 0, 1);

		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(-150, 50, 3, 2, 4, 4);
		miniCuadro(250, 50, 1, 2, 3, 4);
		miniCuadro(-50, 150, 2, 1, 3, 3);
		miniCuadro(150, 150, 1, 3, 3, 3);
		miniCuadro(-50, -50, 1, 3, 4, 3);
		miniCuadro(150, -50, 3, 1, 2, 2);
		miniCuadro(50, -150, 3, 1, 3, 4);

		glLoadIdentity();
		if (vueltas > 4 && vueltas < 14)
			glRotated(-ang, 0, 0, 1);

		miniCuadro(-50, 250, 1, 2, 1, 1);
		miniCuadro(150, 250, 2, 3, 1, 2);
		miniCuadro(-150, 150, 3, 2, 1, 1);
		miniCuadro(250, 150, 3, 1, 2, 1);
		miniCuadro(-250, 50, 3, 1, 3, 3);
		miniCuadro(350, 50, 2, 1, 2, 1);
		miniCuadro(-150, -50, 2, 1, 3, 3);
		miniCuadro(250, -50, 2, 1, 2, 1);
		miniCuadro(-50, -150, 1, 2, 2, 2);
		miniCuadro(150, -150, 3, 2, 3, 3);

		glLoadIdentity();
		if (vueltas > 6 && vueltas < 12)
			glRotated(ang, 0, 0, 1);

		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(250, 250, 3, 1, 4, 3);
		miniCuadro(-250, 150, 2, 1, 4, 4);
		miniCuadro(350, 150, 2, 3, 3, 3);
		miniCuadro(-250, -50, 2, 1, 1, 1);
		miniCuadro(350, -50, 1, 3, 3, 3);
		miniCuadro(-150, -150, 3, 2, 3, 4);
		miniCuadro(250, -150, 2, 3, 1, 1);

		glLoadIdentity();
		if (vueltas > 8 && vueltas < 10)
			glRotated(-ang, 0, 0, 1);

		miniCuadro(-250, 250, 1, 2, 4, 4);
		miniCuadro(350, 250, 3, 1, 4, 4);
		miniCuadro(-250, -150, 1, 3, 2, 1);
		miniCuadro(350, -150, 2, 1, 1, 1);
	}
	else if (movida <= 6) {
				//1
		miniCuadro(-250, 250, 1, 2, 4, 4);
		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(-50, 250, 1, 2, 1, 1);
		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(150, 250, 2, 3, 1, 2);
		miniCuadro(250, 250, 3, 1, 4, 3);
		miniCuadro(350, 250, 3, 1, 4, 4);

		//2
		miniCuadro(-250, 150, 2, 1, 4, 4);
		miniCuadro(-150, 150, 3, 2, 1, 1);
		miniCuadro(150, 150, 1, 3, 3, 3);
		miniCuadro(250, 150, 3, 1, 2, 1);
		miniCuadro(350, 150, 2, 3, 3, 3);

		//3
		miniCuadro(-250, 50, 3, 1, 3, 3);
		miniCuadro(-150, 50, 3, 2, 4, 4);

		//4
		miniCuadro(-250, -50, 2, 1, 1, 1);
		miniCuadro(-150, -50, 2, 1, 3, 3);
		miniCuadro(-50, -50, 1, 3, 4, 3);
		miniCuadro(50, -50, 2, 3, 1, 1);
		miniCuadro(150, -50, 3, 1, 2, 2);
		miniCuadro(250, -50, 2, 1, 2, 1);
		miniCuadro(350, -50, 1, 3, 3, 3);

		//5
		miniCuadro(-250, -150, 1, 3, 2, 1);
		miniCuadro(-150, -150, 3, 2, 3, 4);
		miniCuadro(-50, -150, 1, 2, 2, 2);
		miniCuadro(50, -150, 3, 1, 3, 4);
		miniCuadro(150, -150, 3, 2, 3, 3);
		miniCuadro(250, -150, 2, 3, 1, 1);
		miniCuadro(350, -150, 2, 1, 1, 1);
		switch (movida) {
		case 0:
			miniCuadro(-50, 150, 2, 1, 3, 3);
			miniCuadro(x_value, 50, 1, 3, 2, 1);
			miniCuadro(50, 150, 1, 3, 2, 1);
			miniCuadro(150, 50, 2, 3, 4, 4);
			miniCuadro(250, 50, 1, 2, 3, 4);
			miniCuadro(350, 50, 2, 1, 2, 1);
			break;
		case 1:
			miniCuadro(50, 50, 1, 3, 2, 1);
			miniCuadro(-50, y_value, 2, 1, 3, 3);
			miniCuadro(50, 150, 1, 3, 2, 1);
			miniCuadro(150, 50, 2, 3, 4, 4);
			miniCuadro(250, 50, 1, 2, 3, 4);
			miniCuadro(350, 50, 2, 1, 2, 1);
			break;
		case 2:
			miniCuadro(50, 50, 1, 3, 2, 1);
			miniCuadro(-50, 50, 2, 1, 3, 3);
			miniCuadro(x_value, 150, 1, 3, 2, 1);
			miniCuadro(150, 50, 2, 3, 4, 4);
			miniCuadro(250, 50, 1, 2, 3, 4);
			miniCuadro(350, 50, 2, 1, 2, 1);
			break;
		case 3:
			miniCuadro(50, y_value, 1, 3, 2, 1);
			miniCuadro(-50, 50, 2, 1, 3, 3);
			miniCuadro(-50, 150, 1, 3, 2, 1);
			miniCuadro(150, 50, 2, 3, 4, 4);
			miniCuadro(250, 50, 1, 2, 3, 4);
			miniCuadro(350, 50, 2, 1, 2, 1);
			break;
		case 4:
			miniCuadro(50, 150, 1, 3, 2, 1);
			miniCuadro(-50, 50, 2, 1, 3, 3);
			miniCuadro(-50, 150, 1, 3, 2, 1);
			miniCuadro(x_value, 50, 2, 3, 4, 4);
			miniCuadro(250, 50, 1, 2, 3, 4);
			miniCuadro(350, 50, 2, 1, 2, 1);
			break;
		case 5:
			miniCuadro(50, 150, 1, 3, 2, 1);
			miniCuadro(-50, 50, 2, 1, 3, 3);
			miniCuadro(-50, 150, 1, 3, 2, 1);
			miniCuadro(50, 50, 2, 3, 4, 4);
			miniCuadro(x_value, 50, 1, 2, 3, 4);
			miniCuadro(350, 50, 2, 1, 2, 1);
			break;
		case 6:
			miniCuadro(50, 150, 1, 3, 2, 1);
			miniCuadro(-50, 50, 2, 1, 3, 3);
			miniCuadro(-50, 150, 1, 3, 2, 1);
			miniCuadro(50, 50, 2, 3, 4, 4);
			miniCuadro(150, 50, 1, 2, 3, 4);
			miniCuadro(x_value, 50, 2, 1, 2, 1);
			break;
		}
	}
	else if (movida<=8){
		glScaled(crecimiento, crecimiento, 0);
		miniCuadro(350, 50, 2, 1, 3, 3);

		glLoadIdentity();

		miniCuadro(-250, 250, 1, 2, 4, 4);
		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(-50, 250, 1, 2, 1, 1);
		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(150, 250, 2, 3, 1, 2);
		miniCuadro(250, 250, 3, 1, 4, 3);
		miniCuadro(350, 250, 3, 1, 4, 4);

		//2
		miniCuadro(-250, 150, 2, 1, 4, 4);
		miniCuadro(-150, 150, 3, 2, 1, 1);
		miniCuadro(-50, 150, 1, 3, 2, 1);
		miniCuadro(50, 150, 1, 3, 2, 1);
		miniCuadro(150, 150, 1, 3, 3, 3);
		miniCuadro(250, 150, 3, 1, 2, 1);
		miniCuadro(350, 150, 2, 3, 3, 3);

		//3
		miniCuadro(-250, 50, 3, 1, 3, 3);
		miniCuadro(-150, 50, 3, 2, 4, 4);
		miniCuadro(-50, 50, 2, 1, 3, 3);
		miniCuadro(50, 50, 2, 3, 4, 4);
		miniCuadro(150, 50, 1, 2, 3, 4);
		miniCuadro(250, 50, 2, 1, 2, 1);
		//4
		miniCuadro(-250, -50, 2, 1, 1, 1);
		miniCuadro(-150, -50, 2, 1, 3, 3);
		miniCuadro(-50, -50, 1, 3, 4, 3);
		miniCuadro(50, -50, 2, 3, 1, 1);
		miniCuadro(150, -50, 3, 1, 2, 2);
		miniCuadro(250, -50, 2, 1, 2, 1);
		miniCuadro(350, -50, 1, 3, 3, 3);

		//5
		miniCuadro(-250, -150, 1, 3, 2, 1);
		miniCuadro(-150, -150, 3, 2, 3, 4);
		miniCuadro(-50, -150, 1, 2, 2, 2);
		miniCuadro(50, -150, 3, 1, 3, 4);
		miniCuadro(150, -150, 3, 2, 3, 3);
		miniCuadro(250, -150, 2, 3, 1, 1);
		miniCuadro(350, -150, 2, 1, 1, 1);
	}
	else if (movida == 9) {
		glLoadIdentity();
		glRotated(ang2, 0, 0, 1);
		glScaled(crecimiento, crecimiento, 0);
		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(-50, 150, 1, 3, 2, 1);
		miniCuadro(50, -50, 2, 3, 1, 1);
		miniCuadro(-150, 50, 3, 2, 4, 4);
		miniCuadro(50, 50, 2, 3, 4, 4);
		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(250, 150, 3, 1, 2, 1);
		miniCuadro(350, -50, 1, 3, 3, 3);
		miniCuadro(-250, -150, 1, 3, 2, 1);
		miniCuadro(150, 250, 2, 3, 1, 2);
		miniCuadro(350, 50, 2, 1, 3, 3);
		miniCuadro(-250, -50, 2, 1, 1, 1);
		miniCuadro(-250, 50, 3, 1, 3, 3);
		miniCuadro(250, 250, 3, 1, 4, 3);
		miniCuadro(50, -50, 2, 3, 1, 1);
		miniCuadro(-150, -50, 2, 1, 3, 3);
		miniCuadro(150, -50, 3, 1, 2, 2);
		miniCuadro(-50, 50, 2, 1, 3, 3);
		miniCuadro(350, -150, 2, 1, 1, 1);
		miniCuadro(-50, 250, 1, 2, 1, 1);
		miniCuadro(-250, 150, 2, 1, 4, 4);
		miniCuadro(250, 150, 3, 1, 2, 1);
		miniCuadro(-150, 50, 3, 2, 4, 4);
		miniCuadro(-250, 50, 3, 1, 3, 3);
		miniCuadro(350, 250, 3, 1, 4, 4);
		miniCuadro(150, 150, 1, 3, 3, 3);
		miniCuadro(350, 50, 2, 1, 3, 3);
		miniCuadro(-250, -50, 2, 1, 1, 1);
		miniCuadro(50, 50, 2, 3, 4, 4);
		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(-50, 250, 1, 2, 1, 1);
		miniCuadro(-150, -150, 3, 2, 3, 4);
		miniCuadro(-50, 50, 2, 1, 3, 3);
		miniCuadro(350, -150, 2, 1, 1, 1);
		miniCuadro(350, 250, 3, 1, 4, 4);
		miniCuadro(-50, -50, 1, 3, 4, 3);
		miniCuadro(50, 150, 1, 3, 2, 1);
		miniCuadro(150, -150, 3, 2, 3, 3);
		miniCuadro(150, 250, 2, 3, 1, 2);
		miniCuadro(-150, 150, 3, 2, 1, 1);
		miniCuadro(-150, -50, 2, 1, 3, 3);
		miniCuadro(150, -50, 3, 1, 2, 2);
		miniCuadro(150, 50, 1, 2, 3, 4);
		miniCuadro(250, -150, 2, 3, 1, 1);
		miniCuadro(-250, 250, 1, 2, 4, 4);
		miniCuadro(-50, 150, 1, 3, 2, 1);
		miniCuadro(250, 50, 2, 1, 2, 1);
		miniCuadro(50, -150, 3, 1, 3, 4);
		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(-150, 150, 3, 2, 1, 1);
		miniCuadro(-150, -150, 3, 2, 3, 4);
		miniCuadro(150, -150, 3, 2, 3, 3);
		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(50, 150, 1, 3, 2, 1);
		miniCuadro(250, -50, 2, 1, 2, 1);
		miniCuadro(-50, -150, 1, 2, 2, 2);
		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(-50, -50, 1, 3, 4, 3);
		miniCuadro(250, 50, 2, 1, 2, 1);
		miniCuadro(50, -150, 3, 1, 3, 4);
		miniCuadro(150, 50, 1, 2, 3, 4);
		miniCuadro(250, -150, 2, 3, 1, 1);
		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(350, -50, 1, 3, 3, 3);
		miniCuadro(-250, -150, 1, 3, 2, 1);
		miniCuadro(-250, 250, 1, 2, 4, 4);
		miniCuadro(-250, 150, 2, 1, 4, 4);
		miniCuadro(250, -50, 2, 1, 2, 1);
		miniCuadro(-50, -150, 1, 2, 2, 2);
		miniCuadro(350, 150, 2, 3, 3, 3);
	}
	else {

		glLoadIdentity();
		glTranslated(x_value,y_value, 0);
		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(-50, 150, 1, 3, 2, 1);
		miniCuadro(50, -50, 2, 3, 1, 1);
		miniCuadro(-150, 50, 3, 2, 4, 4);
		miniCuadro(50, 50, 2, 3, 4, 4);


		glLoadIdentity();
		glTranslated(0.5*x_value, 1.5*y_value, 0);
		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(250, 150, 3, 1, 2, 1);
		miniCuadro(350, -50, 1, 3, 3, 3);
		miniCuadro(-250, -150, 1, 3, 2, 1);



		glLoadIdentity();
		glTranslated(0, 2*y_value, 0);
		miniCuadro(150, 250, 2, 3, 1, 2);
		miniCuadro(350, 50, 2, 1, 3, 3);
		miniCuadro(-250, -50, 2, 1, 1, 1);
		miniCuadro(-250, 50, 3, 1, 3, 3);

		glLoadIdentity();
		glTranslated(2*x_value, 0, 0);
		miniCuadro(250, 250, 3, 1, 4, 3);
		miniCuadro(50, -50, 2, 3, 1, 1);
		miniCuadro(-150, -50, 2, 1, 3, 3);
		miniCuadro(150, -50, 3, 1, 2, 2);
		miniCuadro(-50, 50, 2, 1, 3, 3);
		miniCuadro(350, -150, 2, 1, 1, 1);


		glLoadIdentity();
		glTranslated(1.5*x_value, .5*y_value, 0);
		miniCuadro(-50, 250, 1, 2, 1, 1);
		miniCuadro(-250, 150, 2, 1, 4, 4);
		miniCuadro(250, 150, 3, 1, 2, 1);
		miniCuadro(-150, 50, 3, 2, 4, 4);
		miniCuadro(-250, 50, 3, 1, 3, 3);

		glLoadIdentity();
		glTranslated(-x_value, y_value, 0);
		miniCuadro(350, 250, 3, 1, 4, 4);
		miniCuadro(150, 150, 1, 3, 3, 3);
		miniCuadro(350, 50, 2, 1, 3, 3);
		miniCuadro(-250, -50, 2, 1, 1, 1);
		miniCuadro(50, 50, 2, 3, 4, 4);

		glLoadIdentity();
		glTranslated(-0.5*x_value, 1.5*y_value, 0);
		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(-50, 250, 1, 2, 1, 1);
		miniCuadro(-150, -150, 3, 2, 3, 4);
		miniCuadro(-50, 50, 2, 1, 3, 3);
		miniCuadro(350, -150, 2, 1, 1, 1);

		glLoadIdentity();
		glTranslated(-1.5*x_value, .5*y_value, 0);
		miniCuadro(350, 250, 3, 1, 4, 4);
		miniCuadro(-50, -50, 1, 3, 4, 3);
		miniCuadro(50, 150, 1, 3, 2, 1);
		miniCuadro(150, -150, 3, 2, 3, 3);


		glLoadIdentity();
		glTranslated(x_value, -y_value, 0);
		miniCuadro(150, 250, 2, 3, 1, 2);
		miniCuadro(-150, 150, 3, 2, 1, 1);
		miniCuadro(-150, -50, 2, 1, 3, 3);
		miniCuadro(150, -50, 3, 1, 2, 2);
		miniCuadro(150, 50, 1, 2, 3, 4);
		miniCuadro(250, -150, 2, 3, 1, 1);


		glLoadIdentity();
		glTranslated(0.5*x_value, -1.5*y_value, 0);
		miniCuadro(-250, 250, 1, 2, 4, 4);
		miniCuadro(-50, 150, 1, 3, 2, 1);
		miniCuadro(250, 50, 2, 1, 2, 1);
		miniCuadro(50, -150, 3, 1, 3, 4);


		glLoadIdentity();
		glTranslated(1.5*x_value, -.5*y_value, 0);
		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(-150, 150, 3, 2, 1, 1);
		miniCuadro(-150, -150, 3, 2, 3, 4);
		miniCuadro(150, -150, 3, 2, 3, 3);

		glLoadIdentity();
		glTranslated(-x_value, -y_value, 0);
		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(50, 150, 1, 3, 2, 1);
		miniCuadro(250, -50, 2, 1, 2, 1);
		miniCuadro(-50, -150, 1, 2, 2, 2);


		glLoadIdentity();
		glTranslated(-0.5*x_value, -1.5*y_value, 0);
		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(-50, -50, 1, 3, 4, 3);
		miniCuadro(250, 50, 2, 1, 2, 1);
		miniCuadro(50, -150, 3, 1, 3, 4);
		miniCuadro(150, 50, 1, 2, 3, 4);
		miniCuadro(250, -150, 2, 3, 1, 1);

		glLoadIdentity();
		glTranslated(-2 * x_value, 0, 0);
		miniCuadro(-150, 250, 3, 1, 3, 4);
		miniCuadro(50, 250, 1, 3, 1, 1);
		miniCuadro(350, -50, 1, 3, 3, 3);
		miniCuadro(-250, -150, 1, 3, 2, 1);

		glLoadIdentity();
		glTranslated(-1.5*x_value, -.5*y_value, 0);
		miniCuadro(-250, 250, 1, 2, 4, 4);
		miniCuadro(-250, 150, 2, 1, 4, 4);
		miniCuadro(250, -50, 2, 1, 2, 1);
		miniCuadro(-50, -150, 1, 2, 2, 2);		
		miniCuadro(350, 150, 2, 3, 3, 3);
		
	}
	glutSwapBuffers();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100); //Posiciona la ventana
	glutInitWindowSize(400, 300);//Tamaño en pixel
	glutCreateWindow("Ejemplo"); //Titulo de la ventana 
	glEnable(GL_BLEND); //Permite el uso de opacos
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Permite el uso de opacos
	init();
	glutDisplayFunc(cuadro); //Función que pinta
	glutTimerFunc(25, update, 0);
	glutMainLoop();
}