#ifndef NUMPY
#define NUMPY

#include <Poly1d.h>
#include <Vector.h>

extern  double integrate2d(double (*fun)(double,double),Element *el, int nx=11, int ny=11);
extern  int GaussSeidel(Matrix *A, Vector *x, Vector *b, double tol = 1e-5, int maxIt = 200);

#endif