#ifndef MESH2D
#define MESH2D

#include <Element.h>
#include <Vector.h>
#include <Matrix.h>
#include <vector>
#include <iostream>

class Mesh2d
{
	public:
	int x0,y0,x1,y1;
	int nx, ny;
	double hx, hy;
	std::vector<Element> elements;

	std::vector<Vector> nodes;
	Mesh2d();
	Mesh2d(int x0, int y0, int x1, int y1, int nx, int ny);
	int isBorder(int);
};

#endif