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
	Mesh2d(int x0 = 0, int y0 = 0, int x1 = 1, int y1 = 1, int nx = 11, int ny = 11);
	int isBorder(int);
};

#endif