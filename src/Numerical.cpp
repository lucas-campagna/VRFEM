
#include <Vector.h>
#include <Element.h>
#include <vector>
#include <cmath>

using namespace std;


double integrate2d(double (*fun)(double,double),Element *domain, int nx, int ny){
	/*
	Calcula integral da funcao parametro "fun" em um dominio especificado por "domain".
	Implementado apenas para triangulos, domain deve conter tres nós.

	Parametros:

	 - 'fun' deve ser uma funcao escalar em R^2;
	 - domain eh o dominio TRIANGULAR de integracao (TODO: implementar para mais dominios)
	 - nx e ny serah a divisao da malha do dominio de integracao
	*/ 

	Vector v1 = domain->nodeVec(0),
		   v2 = domain->nodeVec(1),
		   v3 = domain->nodeVec(2);

	Vector b1(v1.dim), b2(v1.dim); // basis vectors

	double integral = 0;
	double Ab;

	b1 = (v2 - v1)/(nx-1.);
	b2 = (v3 - v1)/(ny-1.);

	Ab = b1.vec(b2).norm()/(2.0*(nx-1)*(ny-1)); // area da base triangular

	for (int i = 1; i < nx-1; ++i){
		Vector x1(b1.dim),x2(b1.dim),x3(b1.dim);
		for (int j = 1; j < ny-i-1; ++j){
			x1 = b1 * i     + b2 * j     + v1;
			x2 = b1 * (i+1) + b2 * j     + v1;
			x3 = b1 * i     + b2 * (j+1) + v1;

			double h = (fun(x1[0],x1[1]) + fun(x2[0],x2[1]) + fun(x3[0],x3[1]))/3.0; // media das alturas em cada no

			integral += Ab*h;
		}
		for (int j = 1; j < ny-i-2; ++j){
			x1 = b1 * (i+1) + b2 * j     + v1;
			x2 = b1 * i     + b2 * (j+1) + v1;
			x3 = b1 * (i+1) + b2 * (j+1) + v1;

			double h = (fun(x1[0],x1[1]) + fun(x2[0],x2[1]) + fun(x3[0],x3[1]))/3.0; // media das alturas em cada no

			integral += Ab*h;
		}
	}
		return integral;
}


int GaussSeidel(Matrix* A, Vector *x0, Vector* b, double tol, int maxIt){
	/*
	Soluciona problema linea Ax = b
	Parametro x0 é o valor do chute inicial
	*/
	Vector x(x0->dim);
	double diff;

	// for (int i = 0; i < A->nrows; ++i){
	// 	A->row(A->row(i)/(*A)[i][i],i);
	// 	(*b)[i] /= (*A)[i][i];
	// }

	for (int i = 0; i < maxIt; ++i){
		x = (*x0);
		for (int j = 0; j < x.dim; ++j){
			(*x0)[j] = ((*b)[j] - (((*A).row(j) * (*x0)).sum() - (*A)[j][j]*(*x0)[j]))/(*A)[j][j];
		}
		
		diff = (x - (*x0)).norm();
		if(diff < tol)
			return i;
	}
	return maxIt;

}