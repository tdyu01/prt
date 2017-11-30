#pragma once
#include <vector>
#include "Punto2D.h"
class Poligono2D {
private:
	vector<Punto2D*> vertices;
	int nV;
public:
	Poligono2D(int nV)
	{
		this->nV = nV;
		vertices = vector<Punto2D*>();

		for (int i = 0; i < nV; i++)
			vertices.push_back(new Punto2D());
	}
	Punto2D* getVertice(int p)
	{
		return vertices[p];
	}
	void setVertice(int p, Punto2D* v)
	{
		vertices[p]->setX(v->getX());
		vertices[p]->setY(v->getY());
	}
	void setVertice(int p, double x, double y)
	{
		vertices[p]->setX(x);
		vertices[p]->setY(y);
	}
	int cantidadVertices()
	{
		return nV;
	}

	void Trasladar(double dx, double dy)
	{
		for (int i = 0; i < nV; i++)
			vertices[i]->Trasladar(dx, dy);
	}
	void Escalar(Punto2D base, double sx, double sy)
	{
		for (int i = 0; i < nV; i++)
			vertices[i]->Escalar(base, sx, sy);
	}

	void Rotar(Punto2D base, double a)
	{
		for (int i = 0; i < nV; i++)
			vertices[i]->Rotar(base, a);

	}


};
