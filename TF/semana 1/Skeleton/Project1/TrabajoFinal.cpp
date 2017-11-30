#include "libs\glut.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "RgbImage.h"

using namespace std;

char* filename = "PoolWater.bmp";
//char* ground = "VENUS.bmp";

static int slices = 16;
static int stacks = 16;
int width=1200, height=1080;

GLuint texture[2];

//Camera variables
float zoom = 0;
float horizontal = 0;
float vertical = 0;

float transformVal = 0.5f;

//Objects transformations
float rotation=0;
float translationX=0;
float translationY = 0;
float translationZ = -6;
int dir = -1;
static int spin = 0;
static int spinV = 0;

static void resize(int width, int height) {
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar-zoom+horizontal, ar+zoom+horizontal, -1.0-zoom+vertical, 1.0+zoom+vertical, 2.0, 100);

	GLdouble aspecto;

	aspecto = (GLdouble)width / height;
	//gluPerspective(45, aspecto, 10, 25);

	

	glMatrixMode(GL_MODELVIEW);	
	//glLoadIdentity();
}

void LoadTextureFromFile(char *filename)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	RgbImage theTexMap(filename);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

	
}

static void display(void)
{
	resize(width,height);
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	const double a = t*90.0;
	const double b = t*180.0;
	const double c = t*270.0;

	GLfloat position[] = { 0.0, 0.0, 1.5, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	
	/*glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTranslated(0, 0, -25);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-15.0f, -15.0f, 15.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, -15.0f, 15.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, 15.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-15.0f, 15.0f, 15.0f);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glLoadIdentity();*/

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();

	glTranslated(translationX, translationY, translationZ);
		glPushMatrix();
			glRotated((GLdouble)a, 0, 0, 1);
			glColor3d(0.2, 0.2, 0.2);
			glTranslated(0, -2, 0);
			glRotated(60, 1, 0, 0);
			glRotated(a, 0, 0, 1);
			glutSolidSphere(0.5, slices, stacks);
		//glutWireCone(1, 1, slices, stacks);
		glPopMatrix();
		glPushMatrix();
			glRotated((GLdouble)a, 0, 0, 1);
			glTranslated(0, 2, 0);
			glRotated(60, 1, 0, 0);
			glRotated(a, 0, 0, 1);
			glutSolidSphere(0.5, slices, stacks);
		//glutWireCone(1, 1, slices, stacks);
		glPopMatrix();
		glPushMatrix();
			glRotated((GLdouble)a, 0, 0, 1);
			glTranslated(2, 0, 0);
			glRotated(60, 1, 0, 0);
			glRotated(a, 0, 0, 1);
			glutSolidSphere(0.5, slices, stacks);
		//glutWireCone(1, 1, slices, stacks);
		glPopMatrix();
		glPushMatrix();
			glRotated((GLdouble)a, 0, 0, 1);
			glTranslated(-2, 0, 0);
			glRotated(60, 1, 0, 0);
			glRotated(a, 0, 0, 1);
			glutSolidSphere(0.5, slices, stacks);
		//glutWireCone(1, 1, slices, stacks);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glColor3d(0, 1, 0);
		glTranslated(translationX, translationY, translationZ);
		glRotated(rotation, 1, 0, 0);
		glRotated(b, 1, 1, 1);

		glutSolidTorus(0.2, 0.6, slices, stacks);
	glPopMatrix();

	glColor3d(0, 0, 1);
	glPushMatrix();
		glTranslated(translationX, translationY, translationZ);
		glRotated(60-rotation, 1, 0, 0);
		glRotated(c, 1, 1, 1);

		glutSolidTorus(0.1, 0.3, slices, stacks);
	glPopMatrix();

	glColor3d(1, 0, 0);

	glPushMatrix();

		glTranslated(translationX, translationY, translationZ);
		glRotated(60+rotation, 1, 0, 0);
		glRotated(a, 1, 1, 1);
	
		glutSolidTorus(0.2, 1, slices, stacks);
	glPopMatrix();
	
	glPushMatrix();

		glTranslated(translationX, translationY, translationZ);
		glPushMatrix();
			glRotated((GLdouble)b, 0, 0, 1);
			glLightfv(GL_LIGHT0, GL_POSITION, position);
			//glutSolidSphere(1.0, 20, 16);

			glTranslated(0, 1.5, 0);
			glColor3f(1.0, 1.0, 1.0);
		//		glutWireCube(0.1);
			glutSolidSphere(0.2, slices, stacks);
		glPopMatrix();
		glPushMatrix();
			glRotated((GLdouble)a, 0, 1, 1);
		//glutSolidSphere(1.0, 20, 16);

			glTranslated(0, -1.5, -0.5);
			glColor3f(1.0, 0.0, 1.0);
		//		glutWireCube(0.1);
			glutSolidSphere(0.2, slices, stacks);
		glPopMatrix();
		glPushMatrix();
			glRotated((GLdouble)a, 1, 1, 1);
			//glutSolidSphere(1.0, 20, 16);

			glTranslated(1, -1, 0);
			glColor3f(1.0, 0.5, 0);
			//		glutWireCube(0.1);
			glutSolidSphere(0.2, slices, stacks);
		glPopMatrix();
		glPushMatrix();
			glRotated((GLdouble)-a, 1, 1, 1);
			//glutSolidSphere(1.0, 20, 16);

			glTranslated(1, -1, 0);
			glColor3f(0, 1, 0.5);
			//		glutWireCube(0.1);
			glutSolidSphere(0.2, slices, stacks);
		glPopMatrix();
		glPushMatrix();
			glRotated((GLdouble)a, 1, 0, 0);
			//glutSolidSphere(1.0, 20, 16);

			glTranslated(0.0, 1.5, 1.0);
			glColor3f(1.0, 1.0, 0.0);
		//		glutWireCube(0.1);
			glutSolidSphere(0.2, slices, stacks);
		glPopMatrix();
		glPushMatrix();
			glRotated((GLdouble)a, 0, 1, 0);
			glLightfv(GL_LIGHT0, GL_POSITION, position);

			//glutSolidSphere(1.0, 20, 16);

			glTranslated(-1.5, 0.0, 0.0);
			
			glColor3f(0.0, 1.0, 1.0);
		//		glutWireCube(0.1);
			glutSolidSphere(0.2, slices, stacks);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();



	/*glPushMatrix();
	glTranslated(0.0, 0.0, -5.0);
	glPushMatrix();
	glRotated((GLdouble)spin, 1, 0, 0);
	glRotated((GLdouble)spinV, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	//glutSolidSphere(1.0, 20, 16);

	glTranslated(0.0, 0.0, 1.5);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);
	glutWireCube(0.1);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//glutSolidTorus(0.275, 0.85, 8, 15);
	//glRotated(60, 1, 0, 0);
	//glRotated(a, 0, 0, 1);
	glutSolidTorus(0.275, 0.85, 8, 15);
	glPopMatrix();*/

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}




static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(0);
		break;

	case '+':
		slices++;
		stacks++;
		break;

	case '-':
		if (slices>3 && stacks>3)
		{
			slices--;
			stacks--;
		}
		break;
	//Object movement
	case '4':
		translationX -= transformVal;
		break;
	case '6':
		translationX += transformVal;
		break;

	case '8':
		translationY -= transformVal;
		break;

	case '5':
		translationY += transformVal;
		break;

	case '7':
		translationZ -= transformVal;
		break;

	case '9':
		translationZ += transformVal;
		break;

	case '1':
		rotation -= transformVal;
		break;
	case '3':
		rotation += transformVal;
		break;


	//Camera movement
	/////////////////////Full zoom ///////////////////////////////
	case 'p':
		if(zoom>-0.5 && zoom <30)
			zoom+=transformVal;
		else
		{
			zoom = 0;
		}
			cout << zoom<<endl;
		break;		
	case 'l':
		if (zoom > -0.5 && zoom < 30)
			zoom-= transformVal;
		else {
			zoom = 29.5;
		}
			cout << zoom << endl;
		break;
	
	//Horizontal camera movement
	case 'a':
		horizontal -= transformVal;
		break;
	case 'd':
		horizontal += transformVal;
		break;

	//Vertical camera movement
	case 'w':
		vertical -= transformVal;
		break;
	case 's':
		vertical += transformVal;
		break;
	}

	glutPostRedisplay();
}

static void idle(void)
{
	glutPostRedisplay();
}

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


static void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			spin = (spin + 30) % 360;
			glutPostRedisplay();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			spinV = (spinV + 30) % 360;
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}
void myTimeOut(int id)
{
	spin += 1;
	spinV -= 1;

	if (zoom >= 0.5)
		dir = -1;
	if (zoom <= 0)
		dir = 1;

	zoom = zoom + 0.01*dir;

	/*else
		zoom += 0.1;*/
	glutPostRedisplay();
	glutTimerFunc(30, myTimeOut, 0);
}

int main() {
	glutInitWindowSize(width, height);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Trabajo Final Grafica");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutTimerFunc(30, myTimeOut, 0);

	glClearColor(0, 0, 0, 0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	LoadTextureFromFile(filename);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	
	glutMainLoop();

	return EXIT_SUCCESS;
}
