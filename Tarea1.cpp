#include "pch.h"
#include <stdlib.h>
#include "GL/glut.h"
#include <iostream>
#include <cstdlib>
#include <time.h>  
#pragma comment(lib, "glut32.lib")
#define WINDOW_TITLE "Project"
using namespace std;

double pi = 3.14159265359;
double ng = pi / 2; //Noventa grados
//Basado en cuentas de que dentro de cada cuadrado deberia de haber un 
double radio = 75 / sqrt(2); //Radio de los segmentos de circulos
double theta = 1.2309594173407746821; //Mitad del angulo que se forma entre el centro y las dos esquinas del segmento


void init(void) {
	glClearColor(27/255, 27/255, 27/255, 0.0); 
	glMatrixMode(GL_PROJECTION); //
	gluOrtho2D(0.0, 700.0, 0.0, 500.0); //Coordenadas de visualización 
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
		glVertex3f(x-100, y, 0);
		segmentoCirculo(3 * ng - theta, 3*ng + theta, x - 50, y + (radio / 3));
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

void cuadro(void) {
	glClear(GL_COLOR_BUFFER_BIT); //
	//1
	miniCuadro(100, 500, 1, 2, 4, 4);
	miniCuadro(200, 500, 3, 1, 3, 4);
	miniCuadro(300, 500, 1, 2, 1, 1);
	miniCuadro(400, 500, 1, 3, 1, 1);
	miniCuadro(500, 500, 2, 3, 1, 2);
	miniCuadro(600, 500, 3, 1, 4, 3);
	miniCuadro(700, 500, 3, 1, 4, 4);
	
	//2
	miniCuadro(100, 400, 2, 1, 4, 4);
	miniCuadro(200, 400, 3, 2, 1, 1);
	miniCuadro(300, 400, 2, 1, 3, 3);
	miniCuadro(400, 400, 1, 3, 2, 1);
	miniCuadro(500, 400, 1, 3, 3, 3);
	miniCuadro(600, 400, 3, 1, 2, 1);
	miniCuadro(700, 400, 2, 3, 3, 3);

	//3
	miniCuadro(100, 300, 3, 1, 3, 3);
	miniCuadro(200, 300, 3, 2, 4, 4);
	miniCuadro(300, 300, 1, 3, 2, 1);
	miniCuadro(400, 300, 2, 1, 3, 3);
	miniCuadro(500, 300, 2, 3, 4, 4);
	miniCuadro(600, 300, 1, 2, 3, 4);
	miniCuadro(700, 300, 2, 1, 2, 1);

	//4
	miniCuadro(100, 200, 2, 1, 1, 1);
	miniCuadro(200, 200, 2, 1, 3, 3);
	miniCuadro(300, 200, 1, 3, 4, 3);
	miniCuadro(400, 200, 2, 3, 1, 1);
	miniCuadro(500, 200, 3, 1, 2, 2);
	miniCuadro(600, 200, 2, 1, 2, 1);
	miniCuadro(700, 200, 1, 3, 3, 3);
	
	//5
	miniCuadro(100, 100, 1, 3, 2, 1);
	miniCuadro(200, 100, 3, 2, 3, 4);
	miniCuadro(300, 100, 1, 2, 2, 2);
	miniCuadro(400, 100, 3, 1, 3, 4);
	miniCuadro(500, 100, 3, 2, 3, 3);
	miniCuadro(600, 100, 2, 3, 1, 1);
	miniCuadro(700, 100, 2, 1, 1, 1);

	glFlush();
}

void cuadroAleatorio(void) {
	srand(time(0));//Hace que los numeros aleatorios tomen el tiempo como semilla.
	glClear(GL_COLOR_BUFFER_BIT);
	int colorCua, colorCir, rot1, rot2;
	for (int x = 100; x <= 700; x += 100) {
		for (int y = 100; y <= 500; y += 100) {
			colorCua = (rand() % 3) + 1;
			switch (colorCua){//El color del circulo deberia de ser distinto al cuadrado
			case 1:
				colorCir = (rand() % 2) + 2;
				break;
			case 2: 
				colorCir = (rand() % 2) * 2 + 1;
				break;
			case 3:
				colorCir = (rand() % 2) + 1;
			default:
				break;
			}
			if (rand() % 2 == 1) {
				rot1 = (rand() % 2) + 1;
				rot2 = (rand() % 2) + 1;
			}
			else {
				rot1 = (rand() % 2) + 3;
				rot2 = (rand() % 2) + 3;
			}
			miniCuadro(x, y, colorCua, colorCir, rot1, rot2);
		}
	}
	glFlush();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100); //Posiciona la ventana
	glutInitWindowSize(400, 300);//Tamaño en pixel
	glutCreateWindow("Ejemplo"); //Titulo de la ventana 
	glEnable(GL_BLEND); //Permite el uso de opacos
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Permite el uso de opacos
	init();
	glutDisplayFunc(cuadro); //Función que pinta
	glutMainLoop();
}
