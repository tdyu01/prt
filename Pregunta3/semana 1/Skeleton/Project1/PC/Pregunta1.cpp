#include <glut.h>
#include <stdlib.h>

#include "cliplines.h"

//
/* GLUT callback Handlers */

void initRendering() {
	glClearColor(0, 0, 0, 0);
}


static void key(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
	case 'q':
		exit(0);
		break;
	}

	glutPostRedisplay();
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 1.0, 200.0);
}

void Display() {
	int i, j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-15, -15, -40);
	glColor3f(0.3f, 0.3f, 0.3f);


	//Lineas grises que hacen el grid
	//Dibujo de la trama de pixeles
	//lineas horizontales
	glBegin(GL_LINES);
	for (i = 0; i <= 30; i++) {
		glVertex3f(0, i, 0);
		glVertex3f(30, i, 0);
	}
	glEnd();

	//lineas verticales
	glBegin(GL_LINES);
	for (j = 0; j <= 30; j++) {
		glVertex3f(j, 0, 0);
		glVertex3f(j, 30, 0);
	}
	glEnd();

	/////////DIBUJAR EL CUADRA EN DONDE SERA EL LIMITE DE CORTE
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmin, ymax);
	glVertex2f(xmax, ymax);
	glVertex2f(xmax, ymin);
	glEnd();


	/////CORTAMOS SEGMENTO
	CohenSutherlandLineClipAndDraw(10, 13, 18, 20);
	CohenSutherlandLineClipAndDraw(30, 8, 18, 20);
	CohenSutherlandLineClipAndDraw(30, 13, 20, 13);
	CohenSutherlandLineClipAndDraw(20, 13, 20, 5);
	CohenSutherlandLineClipAndDraw(20, 5, 15, 5);
	CohenSutherlandLineClipAndDraw(15, 13, 15, 5);
	CohenSutherlandLineClipAndDraw(10, 13, 15, 13);
	glutSwapBuffers();
	glFlush();
}//dibuja todo

static void idle(void)
{
	glutPostRedisplay();
}


/* Program entry point */

int main() {
	//Step 1: Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);

	//Step2: Create Windows
	glutCreateWindow("Cohen-Sutherland Algorithm");
	initRendering();

	//Step3: Handlers functions
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	//Step4: Main Loop
	glutMainLoop();

	return EXIT_SUCCESS;
}