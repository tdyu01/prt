#pragma once
#define outcode int

#include <iostream>
#include "libs\glut.h"
typedef int OutCode;

using namespace std;

const int INSIDE = 0; // 0000
const int LEFT = 1; // 0001
const int RIGHT = 2; //0010
const int BOTTOM = 4; //0100
const int TOP = 8; //1000

const int xmax = 22;
const int xmin = 8;
const int ymin = 8;
const int ymax = 17;

OutCode ComputeOutCode(double x, double y)
{
	//Se ponen las reglas
	OutCode code;
	code = INSIDE;
	if (x < xmin)
		code |= LEFT;
	else if (x > xmax)
		code |= RIGHT;
	if (y < ymin)
		code |= BOTTOM;
	else if (y > ymax)
		code |= TOP;
	return code;
}

void CohenSutherlandLineClipAndDraw(double x0, double y0, double x1, double y1)
{
	OutCode outcode0 = ComputeOutCode(x0, y0);
	OutCode outcode1 = ComputeOutCode(x1, y1);

	bool accept = false;

	while (true)
	{
		if (!(outcode0 | outcode1))
		{
			accept = true;
			break;
		}
		else if (outcode0 & outcode1)
		{
			break;
		}
		else
		{
			double x, y;
			OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

			if (outcodeOut & TOP)
			{
				x = x0 + (x1 - x0)*(ymax - y0) / (y1 - y0);
				y = ymax;
			}
			else if (outcodeOut & BOTTOM)
			{
				x = x0 + (x1 - x0)*(ymin - y0) / (y1 - y0);
				y = ymin;
			}
			else if (outcodeOut & RIGHT)
			{
				y = y0 + (y1 - y0)*(xmax - x0) / (x1 - x0);
				x = xmax;
			}
			else if (outcodeOut & LEFT)
			{
				y = y0 + (y1 - y0)*(xmin - x0) / (x1 - x0);
				x = xmin;
			}

			if (outcodeOut == outcode0)
			{
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode(x0, y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1);
			}
		}

	}

	if (accept)
	{
		//DrawRectangle(xmin, ymin, xmax, ymax);
		
		
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(5.f);
		glBegin(GL_LINES);
		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
		glEnd();
	}
}