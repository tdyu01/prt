#pragma once
#include <vector>
#include "Poligono2D.h"
using namespace std;
class Malla2D {
private:
	vector<Poligono2D*> poligonos;
public:
	Malla2D()
	{
		/*poligonos = vector<Poligono2D*>*();*/
		
	}

	void addPoligono(Poligono2D* pol)
	{
		poligonos.push_back(pol);
	}

	int getCantidadPoligonos()
	{
		return poligonos.size();
	}

	Poligono2D* getPoligono(int p)
	{
		return poligonos[p];
	}

	void Trasladar(Punto2D* vertice, double dx, double dy)
	{
		int i, j;
		for (int i = 0; i < getCantidadPoligonos(); i++)
		{
			Poligono2D* pol;
			pol = getPoligono(i);
			for (int j = 0; j < pol->cantidadVertices(); j++)
			{
				Punto2D* vpol;
				vpol = pol->getVertice(j);
				if (vpol==vertice)
				{
					vpol->Trasladar(dx, dy);
				}
			}
		}
	}

};