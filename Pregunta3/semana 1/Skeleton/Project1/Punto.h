#pragma once
#include <cmath>
using namespace std;
class Punto2D {
private:

//	Punto2D(double x, double y):x(x),y(y)
//	{
//	}
//
//	Punto2D()
//	{
//		this->x = 0;
//		this->y = 0;
//	}
//
//	double GetX()
//	{
//		return x;
//	}
//
//	void SetX(double x)
//	{
//		this->x = x;
//	}
//
//	double GetY()
//	{
//		return y;
//	}
//
//	void SetY(double y)
//	{
//		this->y = y;
//	}
//
//	//Bezier
//	const Punto2D & operator=(const Punto2D &rPunto2D)
//	{
//		x = rPunto2D.x;
//		y = rPunto2D.y;
//		z = rPunto2D.z;
//		return *this;
//	}
//
//
//	void Trasladar(double dx, double dy)
//	{
//		x = dx + x;
//		y = dy + y;
//		/*return this;*/
//	}
//
//	void Escalar(double sx, double sy)
//	{
//		x = sx * x;
//		y = sy * y;
//		/*return this;*/
//	}
//
//	void Escalar(Punto2D* base, double sx, double sy)
//	{
//		Trasladar(-base->GetX(), -base->GetY());
//		Escalar(sx, sy);
//		Trasladar(base->GetX(), base->GetY());
//		//return this;
//	}
//
//	void Rotar(double a)
//	{
//		double ca, sa, xp;
//
//		ca = cos(a);
//		sa = sin(a);
//		
//		xp = x*ca - y*sa;
//		y = x*sa + y*ca;
//		
//		x = xp;
//		/*return this;*/
//	}
//
//	Punto2D* Rotar(Punto2D* base, double a)
//	{
//		Trasladar(-base->GetX(), -base->GetY());
//		Rotar(a);
//		Trasladar(base->GetX(), base->GetY());
//		return this;
//	}
//
//	bool equals(Punto2D p)
//	{
//		Punto2D b = p;
//		return x == p.GetX() && y == p.GetY();
//	}

	double x, y, z;

public:

	double x1, y1, z1;//Bezier

	Punto2D()
	{
		x = y = 0;
	}
	Punto2D(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	double getX() {
		return x;
	}
	void setX(double x) {
		this->x = x;
	}
	double getY() {
		return y;
	}
	void setY(double y) {
		this->y = y;
	}

	void Trasladar(double dx, double dy)
	{
		x = dx + x;  // x += dx;
		y = dy + y;  // y += dy;
					 /*return this;*/
	}
	void Escalar(double sx, double sy)
	{
		x = sx * x;
		y = sy * y;
		
	}
	void Escalar(Punto2D base, double sx, double sy)
	{
		Trasladar(-base.getX(), -base.getY());
		Escalar(sx, sy);
		Trasladar(base.getX(), base.getY());
	}
	void Rotar(double a)
	{
		double ca, sa, xp;

		ca = cos(a);
		sa = sin(a);
		xp = x * ca - y * sa;
		y = x * sa + y * ca;
		x = xp;
		
	}
	void Rotar(Punto2D base, double a)
	{
		Trasladar(-base.getX(), -base.getY());
		Rotar(a);
		Trasladar(base.getX(), base.getY());
		
	}
	//Bezier
	void init()
	{
		x1 = 0;
		y1 = 0;
		z1 = 0;
	}

	void setxy(double x2, float y2)
	{
		x1 = x2;
		y1 = y2;
		z1 = 0;
	}
	const Punto2D & operator=(const Punto2D &rPuntos2D)
	{
		x1 = rPuntos2D.x1;
		y1 = rPuntos2D.y1;
		z1 = rPuntos2D.z1;
		return*this;
	}

	bool equals(Punto2D p)
	{
		Punto2D b = p;
		return x == p.getX() && y == p.getY();
	}

};

