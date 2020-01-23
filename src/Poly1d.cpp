#include <Poly1d.h>



Poly1d::Poly1d(int dim) : dim(dim) {a.resize(dim); b = 0.0;}

Poly1d::Poly1d(double A, double B) : b(B) {a.resize(1);a[0] = A; dim = 1;}

Poly1d::Poly1d(Vector A, double B) : b(B) {a.resize(A.dim);	a = A;	dim = A.dim;}

double Poly1d::operator() (Vector x){return x.dot(a) + b;}
double Poly1d::operator() (double x){assert(dim == 1); return x * a[0] + b;}
double Poly1d::operator() (double x,double y){assert(dim == 2); return x * a[0] + y * a[1] + b;}
double Poly1d::operator() (double x,double y,double z){assert(dim == 3); return x * a[0] + y * a[1] + z * a[2] + b;}




double* Poly1d::operator() (double x[], int n){
	assert(dim == 1);
	double *vec = new double[n];
	for(int i=0;i<n;i++)
		vec[i] =  x[i] * a[0] + b;
	return vec;
}

double* Poly1d::operator() (double ini, double end, int n){
	assert(dim == 1);
	double x[n];
	double dx = (end - ini)/(n - 1);
	for(int i=0;i<n;i++)
		x[i] = ini + dx*i;
	return (*this)(x,n);

}

Poly1d Poly1d::operator/(double val){
	Poly1d p(a,b);
	p.a /= val;
	p.b /= val;
	return p;
}