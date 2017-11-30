//#pragma once
//#include "libs\glut.h"
//#include "Poligono2D.h"
//#include <cmath>
//#include <math.h>
//
//double pi = 3.1415926535897;
//using namespace std;
//class Renderer
//{
//private:
//	float v_x, v_y, v_z;
//	int gridX, gridY;
//	Poligono2D* Pol;
//	int ipb;
//	Punto2D* base;
//	int tipoTransformacion;
//	int rotar;
//	double espesor;
//public:
//	Renderer()
//	{
//		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//		glutInitWindowSize(400, 400);
//		
//		//step2: Create Window
//		glutCreateWindow("Skeleton - ejercicio ejemplo");
//		//initRendering();
//		
//		//step3: Callbacks - Setear máquina de estados.
//		glutDisplayFunc(display);
//		glutReshapeFunc(reshape);
//		
//		//step4: Main Loop
//		glutMainLoop();
//
//		gridX = 30;
//		gridY = 30;
//		v_x = -gridX / 2;
//		v_y = -gridY / 2;
//		v_z = -40;
//
//		Pol = new Poligono2D(5);
//		Pol->setVertice(0, 10, 12);
//		Pol->setVertice(1, 16, 12);
//		Pol->setVertice(2, 16, 18);
//		Pol->setVertice(3, 13, 21);
//		Pol->setVertice(4, 10, 18);
//
//		base = new Punto2D();
//		ipb = 0;
//		tipoTransformacion = 0;
//		rotar = 0;
//		espesor = 1;
//
//	}
//	void display()
//	{
//		int i, j;
//
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glMatrixMode(GL_MODELVIEW);
//		glLoadIdentity();
//
//		glTranslatef(v_x, v_y, v_z);
//		glRotatef(45, 1, 0, 0);
//
//		glColor3f(0.3f, 0.3f, 0.3f);
//		//lineas horizontales
//		glBegin(GL_LINES);
//		for (i = 0; i <= gridY; i++) {
//			glVertex3f(0, i, 0);
//			glVertex3f(gridX, i, 0);
//		}
//		glEnd();
//
//		//lineas verticales
//		glBegin(GL_LINES);
//		for (i = 0; i <= gridX; i++) {
//			glVertex3f(i, 0, 0);
//			glVertex3f(i, gridY, 0);
//		}
//		glEnd();
//
//		glClear(GL_DEPTH_BUFFER_BIT);
//		glPointSize(5.0f);
//		glColor3f(0.6f, 0.6f, 0.6f);
//		glBegin(GL_POINTS);
//		for (i = 0; i <= gridX; i++)
//			for (j = 0; j <= gridY; j++)
//				glVertex3f(i, j, 0);
//		glEnd();
//
//
//
//		base->SetX(Pol->getVertice(ipb).GetX());
//		base->SetY(Pol->getVertice(ipb).GetY());
//
//		if (rotar != 0)
//			if (rotar > 0) {
//				Pol->Rotar(base, 1*180/pi );
//				rotar--;
//			}
//			else {
//				Pol->Rotar(base, -1*180/pi);
//				rotar++;
//			}
//
//
//			glColor3f(1, 1, 1);
//			glBegin(GL_LINE_LOOP);
//			glVertex3d(base->GetX() - 0.5f, base->GetY() - 0.5f, 0);
//			glVertex3d(base->GetX() + 0.5f, base->GetY() - 0.5f, 0);
//			glVertex3d(base->GetX() + 0.5f, base->GetY() + 0.5f, 0);
//			glVertex3d(base->GetX() - 0.5f, base->GetY() + 0.5f, 0);
//			glEnd();
//
//			glClear(GL_DEPTH_BUFFER_BIT);
//			glColor3f(1, 1, 0);
//			glBegin(GL_LINE_LOOP);
//			for (i = 0; i < Pol->cantidadVertices(); i++)
//			{
//				Punto2D* v = Pol->getVertice(i);
//				glVertex3d(v->GetX(), v->GetY(), 0);
//			}
//			glEnd();
//
//			glBegin(GL_LINE_LOOP);
//			for (i = 0; i < Pol->cantidadVertices(); i++)
//			{
//				Punto2D v = Pol->getVertice(i);
//				glVertex3d(v->GetX(), v->GetY(), espesor);
//			}
//			glEnd();
//
//			glBegin(GL_LINES);
//			for (i = 0; i < Pol->cantidadVertices(); i++)
//			{
//				Punto2D v = Pol->getVertice(i);
//				glVertex3d(v->GetX(), v->GetY(), 0);
//				glVertex3d(v->GetX(), v->GetY(), espesor);
//			}
//			glEnd();
//
//
//			glFlush();
//	}
//
//	void displayChanged()
//	{
//		display();
//	}
//
//	void init()
//	{
//		glClearColor(0, 0, 0, 0);
//		glEnable(GL_DEPTH_TEST);
//	}
//	
//	void reshape(int x, int y, int width, int height)
//	{
//	
//		glViewport(0, 0, width, height);
//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//		gluPerspective(45.0, (double)width / height, 0.1, 1000);
//		glMatrixMode(GL_MODELVIEW);
//		glLoadIdentity();
//
//	}
//	void reshape(int width, int height)
//	{
//		reshape(0, 0, width, height);
//	}
//
//	void keyTyped(KeyEvent key)
//	{
//	}
//
//	public void keyPressed(KeyEvent key)
//	{
//		switch (key.getKeyCode()) {
//		case KeyEvent.VK_ESCAPE:
//			System.exit(0);
//			break;
//		case KeyEvent.VK_F1:
//			ipb = (ipb + 1) % Pol->cantidadVertices();
//			break;
//		case KeyEvent.VK_F2:
//			tipoTransformacion = (tipoTransformacion + 1) % 3;
//			break;
//		case KeyEvent.VK_F3:
//			rotar = 45;
//			break;
//		case KeyEvent.VK_F4:
//			rotar = -45;
//			break;
//		case KeyEvent.VK_F5:
//			espesor += 0.1;
//			break;
//		case KeyEvent.VK_F6:
//			espesor -= 0.1;
//			break;
//
//		case KeyEvent.VK_PAGE_UP:
//			v_z = v_z - 1;
//			break;
//		case KeyEvent.VK_PAGE_DOWN:
//			v_z = v_z + 1;
//			break;
//		case KeyEvent.VK_RIGHT:
//			if (tipoTransformacion == 0)
//				Pol->Trasladar(1, 0);
//			if (tipoTransformacion == 1)
//				Pol->Escalar(base, 1.1, 1);
//			if (tipoTransformacion == 2)
//				Pol->Rotar(base, -0.1);
//
//			break;
//		case KeyEvent.VK_LEFT:
//			if (tipoTransformacion == 0)
//				Pol->Trasladar(-1, 0);
//			if (tipoTransformacion == 1)
//				Pol->Escalar(base, 0.9, 1);
//			if (tipoTransformacion == 2)
//				Pol->Rotar(base, 0.1);
//			break;
//		case KeyEvent.VK_UP:
//			if (tipoTransformacion == 0)
//				Pol->Trasladar(0, 1);
//			if (tipoTransformacion == 1)
//				Pol->Escalar(base, 1, 1.1);
//			break;
//		case KeyEvent.VK_DOWN:
//			if (tipoTransformacion == 0)
//				Pol->Trasladar(0, -1);
//			if (tipoTransformacion == 1)
//				Pol->Escalar(base, 1, 0.9);
//			break;
//
//		case KeyEvent.VK_A:
//			string ayuda ="F1: Cambia de punto" + "\n" + "ESC: Salir" + "\n";
//			break;
//		default:
//			break;
//		}
//	}
//
//	public void keyReleased(KeyEvent key)
//	{
//	}
//
//}