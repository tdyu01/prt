#include<iostream>
#include <stdlib.h>
#include <glut.h>
#include <Windows.h>
#include "math.h"
#include "vector"
#include "glut.h"
#include "Punto2D.h"
using namespace std;
int gridX = 30;
int gridY = 30;
Punto2D* base;
int SCREEN_HEIGHT = 480;
int NUMPOINTS = 0;
vector<Punto2D> puntosControl;
void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
void DibujarPunto(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void DibujarLinea(Punto2D p1, Punto2D p2)
{
	glBegin(GL_LINES);
	glVertex3f(p1.x1, p1.y1, p1.z1);
	glVertex3f(p2.x1, p2.y1, p2.z1);
	glEnd();
		glPushMatrix();
		glTranslatef((p1.x1 + p2.x1) / 2, (p1.y1 + p2.y1) / 2, (p1.z1 - 5.0 + p2.z1) / 2);
		glutSolidSphere(20, 15, 15);
	glPopMatrix();
	glFlush();
}

int Factorial(int x)
{
	int fact = 1;
	for (int i = 2; i <= x; i++)
	{
		fact *= i;
	}
	return fact;
}

int CoeficienteBinomial(int n, int i)
{
	int a = Factorial(n);
	int b = Factorial(i);
	int c = Factorial(n - i);
	int cb = a / (b*c);
	return cb;
}

Punto2D DibujarBezier(double t)
{
	Punto2D P;
	P.init();
	int n = NUMPOINTS - 1;
	for (int i = 0; i < NUMPOINTS; i++)
	{
		P.x1 += CoeficienteBinomial(n, i)*(puntosControl[i].x1)*(pow((1 - t), n - i)*pow(t, i));
		P.y1 += CoeficienteBinomial(n, i)*(puntosControl[i].y1)*(pow((1 - t), n - i)*pow(t, i));
	}
	return P;
}

void Mykey(int key, int x, int y)
{
	if (key == GLUT_KEY_F1 && puntosControl.size() > 2)
	{
		glColor3f(1.0, 1.0, 1.0);
		for (int i = 0; i < NUMPOINTS - 1; i++)
		{
			DibujarLinea(puntosControl[i], puntosControl[i + 1]);
		}
		glColor3f(0.0, 1.0, 1.0);
		Punto2D POld = puntosControl[0];
		for (double t = 0.0; t <= 1.0; t += 0.005)
		{
			Punto2D P = DibujarBezier(t);
			DibujarLinea(POld, P);
			POld = P;
		}
		glColor3f(1.0, 1.0, 0.0);
	}
}
void MyMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON&& state == GLUT_DOWN)
	{
		Punto2D aux;
		aux.setxy((float)x, (float)(SCREEN_HEIGHT - y));
		puntosControl.push_back(aux);
		NUMPOINTS++;
		DibujarPunto(x, SCREEN_HEIGHT - y);
	}
}
int main(int argc, char *argv[])
{
	////Bezier
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Curva de Bezier: ");
	glutMouseFunc(MyMouse);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(Mykey);
	myInit();
	glutMainLoop();
	return(0);
}