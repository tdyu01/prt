

#include <glut.h>
#include <stdlib.h>
#include <math.h>

#include "operations.h"

#define DEGTORAD (2 * 3.14159 / 360)

enum { SPHERE = 1, CONE };
int csg_op = CSG_A; //default csg operation
GLfloat viewangle;

/////////////////////////////////////////////////////////////////
//Drawing Two Objects 
/////////////////////////////////////////////////////////////////

// Draw a sphere
GLfloat sphereX = 0.f, sphereY = 0.f, sphereZ = 0.f;
void sphere(void) {
	glPushMatrix();
	glTranslatef(sphereX, sphereY, sphereZ);
	glCallList(SPHERE);
	glPopMatrix();
}

// Draw a cone
GLfloat coneX = 0.f, coneY = 0.f, coneZ = 0.f;
void cone(void) {
	glPushMatrix();
	glTranslatef(coneX, coneY, coneZ);
	glTranslatef(0.f, 0.f, -30.f);
	glCallList(CONE);
	glPopMatrix();
}

/////////////////////////////////////////////////////////////////
//Animation Support
/////////////////////////////////////////////////////////////////
enum { ANIM_LEFT, ANIM_RIGHT };
int animDirection = ANIM_LEFT;

static void
anim(void) {
	if (animDirection == ANIM_LEFT)
		viewangle -= 3.f;
	else
		viewangle += 3.f;
	glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////
//Callbacks
///////////////////////////////////////////////////////////////////////////

static void
menu(int csgop) {
	csg_op = csgop;
	glutPostRedisplay();
}

static void
display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glPushMatrix();
	glRotatef(viewangle, 0.f, 1.f, 0.f);
	switch (csg_op) {
	case CSG_A: _one(cone);   break;
	case CSG_B:	_one(sphere); break;
	case CSG_A_OR_B:  _or(cone, sphere);  break;
	case CSG_A_AND_B: _and(cone, sphere); break;
	case CSG_A_SUB_B: _sub(cone, sphere); break;
	case CSG_B_SUB_A: _sub(sphere, cone); break;
	}
	glPopMatrix();
	glutSwapBuffers();
}

static void
special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		glutIdleFunc(anim);
		animDirection = ANIM_LEFT;
		break;
	case GLUT_KEY_RIGHT:
		glutIdleFunc(anim);
		animDirection = ANIM_RIGHT;
		break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		glutIdleFunc(0);
		break;
	}
}

static void
key(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		viewangle -= 10.f;
		glutPostRedisplay();
		break;
	case 's':
		viewangle += 10.f;
		glutPostRedisplay();
		break;
	case '\033': /*Escape*/
		exit(0);
	}
}

int picked_object;
int xpos = 0, ypos = 0;
int newxpos, newypos;
int startx, starty;

static void
mouse(int button, int state, int x, int y) {
	if (state == GLUT_UP) {
		picked_object = button;
		xpos += newxpos;
		ypos += newypos;
		newxpos = 0;
		newypos = 0;
	}
	else {              /* GLUT_DOWN */
		startx = x;
		starty = y;
	}
}

static void
motion(int x, int y) {
	GLfloat r, objx, objy, objz;

	newxpos = x - startx;
	newypos = starty - y;

	r = (newxpos + xpos) * 50.f / 512.f;
	objx = r * cos(viewangle * DEGTORAD);
	objy = (newypos + ypos) * 50.f / 512.f;
	objz = r * sin(viewangle * DEGTORAD);

	switch (picked_object) {
	case CSG_A:
		coneX = objx;
		coneY = objy;
		coneZ = objz;
		break;
	case CSG_B:
		sphereX = objx;
		sphereY = objy;
		sphereZ = objz;
		break;
	}
	glutPostRedisplay();
}


//Main Operation
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(512, 512);
	glutInitDisplayMode(GLUT_STENCIL | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("CSG Example Operations");
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	//create a Menu
	glutCreateMenu(menu);
	glutAddMenuEntry("A only", CSG_A);
	glutAddMenuEntry("B only", CSG_B);
	glutAddMenuEntry("A or B", CSG_A_OR_B);
	glutAddMenuEntry("A and B", CSG_A_AND_B);
	glutAddMenuEntry("A sub B", CSG_A_SUB_B);
	glutAddMenuEntry("B sub A", CSG_B_SUB_A);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	////
	static GLfloat lightpos[] = { -20.f, 0.f, 90.f, 0.0f };
	static GLfloat sphere_mat[] = { 1.f, .0f, 0.f, 1.f };
	static GLfloat cone_mat[] = { 0.f, .5f, 1.f, 1.f };

	GLUquadricObj *sphere, *cone, *base;

	///
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


	glNewList(SPHERE, GL_COMPILE);
	sphere = gluNewQuadric();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sphere_mat);
	gluSphere(sphere, 20.f, 64, 64);
	gluDeleteQuadric(sphere);
	glEndList();

	glNewList(CONE, GL_COMPILE);
	cone = gluNewQuadric();
	base = gluNewQuadric();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cone_mat);
	gluQuadricOrientation(base, GLU_INSIDE);
	gluDisk(base, 0., 15., 64, 1);
	gluCylinder(cone, 15., 0., 60., 64, 64);
	gluDeleteQuadric(cone);
	gluDeleteQuadric(base);
	glEndList();

	glMatrixMode(GL_PROJECTION);
	glOrtho(-50., 50., -50., 50., -50., 50.);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();
	return 0;
}