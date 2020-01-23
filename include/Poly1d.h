#ifndef POLY1D
#define POLY1D


#include <Vector.h>
#include <vector>
#include <cassert>
#include <iostream>

class Poly1d{
	public:
		int dim;
		Vector a;
		double b;


	Poly1d(int dim);
	Poly1d(double A, double B);
	Poly1d(Vector A, double B);

	double operator() (Vector);
	double operator() (double);
	double operator() (double,double);
	double operator() (double,double,double);
	double* operator() (double *, int);
	double* operator() (double, double, int);

	Poly1d operator/(double);
};

#endif