#ifndef ELEMENT
#define ELEMENT

#include <Poly1d.h>
#include <Matrix.h>
#include <Vector.h>
#include <vector>
#include <cassert>
#include <cmath>
#include <initializer_list>


// Elementos precisam estar inseridos em uma malha,
// por isso possuem um ponteiro para a grade de nós da mesma.

class Element
{
	std::vector<Vector> *pNodes;
	std::vector<int> map; // list to map local -> global nodes
public:
	int nNodes;
	double area;
	// int nNodes; // number of nodes
	Element(int); // enter with number of nodes, all = 0
	Element(std::vector<int>, std::vector<Vector> *); // enter with indexes
	// Element(int, int); // enter with index interval

	Poly1d shapef(int); // shape function of node i

	void calc_area();
	void set_pNodes(std::vector<Vector> *nodes);

	int & operator[](int);

	Vector nodeVec (int);

	double integrate(double (*fun)(double,double),int i, int nx=11, int ny=11);

};

#endif