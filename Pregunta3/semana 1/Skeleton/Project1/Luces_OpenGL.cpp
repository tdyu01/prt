//#include "libs\glut.h"
//
//void initializing()
//{
//	//Inicializar el color del buffer
//	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
//	GLfloat mat_shininess[] = { 50.0 };
//	GLfloat light_position[] = { 1.0,1.0,1.0,0.0 };
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glShadeModel(GL_SMOOTH);
//
//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_DEPTH_TEST);
//}
//
//void Disp()
//{
//	//Matriz de camara, matriz del model
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glutSolidSphere(1.0, 20, 16);
//
//	glFlush();
//	
//}
//
//
//void Reshape(int w, int h)
//{
//	//Tarea: Transformación de coordenadas(geometría analítica)
//	glViewport(0, 0, w, h); //puerto de visualizacion
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	if (w <= h)
//	{
//		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -10, 10);
//	}
//	else
//	{
//		glOrtho(-1.5*(GLfloat)w / (GLfloat)h, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10, 10);
//	}
//	//Modifica la perspectiva en frustrum(por revisar)
//	//gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 1.0, 400.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//
//int main()
//{
//	//Inicializar Glut
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(500, 500);
//
//	//Crear ventanas
//	glutCreateWindow("Lights");
//	initializing();
//	glutDisplayFunc(Disp);
//	glutReshapeFunc(Reshape);
//
//	//Loop principal
//	glutMainLoop();
//
//	return 0;
//}


//#include "libs\glut.h"
//
//static int spin = 0;
//
//static void initializing(void)
//{
//	//Inicializar el color del buffer
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glShadeModel(GL_SMOOTH);
//
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_DEPTH_TEST);
//}
//
//static void Disp(void)
//{
//	GLfloat position[] = { 0.0,0.0,1.5,1.0 };
//	//Matriz de camara, matriz del model
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glPushMatrix();
//	glTranslatef(0.0, 0.0, -5.0);
//	
//	glPushMatrix();
//	glRotated((GLdouble)spin, 1.0, 0.0, 0.0);
//	glLightfv(GL_LIGHT0, GL_POSITION, position);
//
//	glTranslated(0.0, 0.0, 1.5);
//	glDisable(GL_LIGHTING);
//	glColor3f(0.0, 1.0, 1.0);
//	glutWireCube(0.1);
//	glEnable(GL_LIGHTING);
//	glPopMatrix();
//
//	glutSolidTorus(0.275, 0.85, 8, 15);
//	glPopMatrix();
//	glFlush();
//
//}
//
//
//
//static void Reshape(int w, int h)
//{
//	//Tarea: Transformación de coordenadas(geometría analítica)
//	glViewport(0, 0, w, h); //puerto de visualizacion
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	//Modifica la perspectiva en frustrum(por revisar)
//	gluPerspective(40.0, (GLdouble)w / (GLdouble)h, 1.0, 400.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//static void mouse(int button, int state, int x, int y)
//{
//	switch (button)
//	{
//	case GLUT_LEFT_BUTTON:
//		if (state == GLUT_DOWN)
//		{
//			spin = (spin + 30) % 360;
//			glutPostRedisplay();
//		}
//		break;
//	default:
//		break;
//	}
//}
//
//
//int main()
//{
//	//Inicializar Glut
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(500, 500);
//
//	//Crear ventanas
//	glutCreateWindow("Lights2");
//	initializing();
//	glutDisplayFunc(Disp);
//	glutReshapeFunc(Reshape);
//	glutMouseFunc(mouse);
//	//Loop principal
//	glutMainLoop();
//
//	return 0;
//}