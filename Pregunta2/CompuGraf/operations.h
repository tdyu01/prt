#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <glut.h>
enum {
	CSG_A,
	CSG_B,
	CSG_A_OR_B,
	CSG_A_AND_B,
	CSG_A_SUB_B,
	CSG_B_SUB_A
};

static void
_one(void(*dso)(void)) {
	glEnable(GL_DEPTH_TEST);
	dso(); // 
	glDisable(GL_DEPTH_TEST);
}

static void
firstInsideSecond(void(*a)(void), void(*b)(void), GLenum face, GLenum test) {
	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glCullFace(face);
	a();

	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 0, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glCullFace(GL_BACK);
	b();

	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	glCullFace(GL_FRONT);
	b();
	glDepthMask(GL_TRUE);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glStencilFunc(test, 0, 1);
	glDisable(GL_DEPTH_TEST);

	glCullFace(face);
	a();                  /* draw the part of a that's in b */
}

static void
fixDepth(void(*a) (void)) {
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glDepthFunc(GL_ALWAYS);
	a();                  /* draw the front face of a, fixing the depth buffer */
	glDepthFunc(GL_LESS);
}

////////////////////////////////////////////////////////////////////////////////
/// AND, OR and SUBSTRACT OPERATION SUPPORT
////////////////////////////////////////////////////////////////////////////////

// OR Operation: Draw both objects with depth buffering on
static void
_or(void(*a)(void), void(*b)(void)) {
	glEnable(GL_DEPTH_TEST);
	a();
	b();
	glDisable(GL_DEPTH_TEST);
}

// AND Operation:* "and" two objects together
static void
_and(void(*a)(void), void(*b)(void)) {
	firstInsideSecond(a, b, GL_BACK, GL_NOTEQUAL);
	fixDepth(b);////
	firstInsideSecond(b, a, GL_BACK, GL_NOTEQUAL);
	glDisable(GL_STENCIL_TEST);  /* reset things */
}

// Subtract Operation: substract b from a
static void
_sub(void(*a)(void), void(*b) (void)) {
	firstInsideSecond(a, b, GL_FRONT, GL_NOTEQUAL);
	fixDepth(b); /////
	firstInsideSecond(b, a, GL_BACK, GL_EQUAL);
	glDisable(GL_STENCIL_TEST);  /* reset things */
}

#endif
