#include <iostream>
#include <fstream>
#include <Vector.h>
#include <Poly1d.h>
#include <Element.h>
#include <Mesh2d.h>
#include <Matrix.h>
#include <string>
#include <vector>
#include <Numerical.h>
#include "mkl.h"


using namespace std;

/*
Primeira versao de um programa de elementos finitos para resolver equacao de laplace
*/

double fun(double x, double y){
	if(abs(x - 0.1) < 0.05 && abs(y - 0.5) < 0.4)
		return 1; // hot
	if(abs(x - 0.5) < 0.2 && abs(y - 0.5) < 0.05)
		return -1; // cold
	if(abs(x - 0.9) < 0.05 && abs(y - 0.5) < 0.4)
		return 1; // hot
	return 0; // room temp
}

int main(int argc, char **argv){
	Mesh2d mesh(0,0,1,1,41,41);
	
	Matrix A(mesh.nodes.size());
	Vector b(mesh.nodes.size());
	Vector x(mesh.nodes.size());

	ofstream fforce("force.dat"), foutput("output.dat");


	// // Assemblagem
	for(auto el: mesh.elements){
		Poly1d p_i(2), p_j(2); // polinomio bidimensional (x,y)


		for(int i = 0; i < el.nNodes; i++){ // i = local index
			int n = el[i]; // n = global index
			double f = 0;

			p_i = el.shapef(i);
			cout << "passou shapef(i="<<i<<")" << endl;

			// eq 55
			f = el.integrate(&fun,i);

			for(int j = 0; j < el.nNodes; j++){ // j = local index
				int m = el[j]; // m = global index
				double K;
				
				p_j = el.shapef(j);
				cout << "passou shapef(j="<<j<<")" << endl;

				K = el.area * (p_i.b + p_i.a[0]*p_j.a[0] + p_i.a[1]*p_j.a[1]);

				if(!mesh.isBorder(n) && !mesh.isBorder(m)){
				// eq 54
					A[n][m] += K;
					b[n] += f;
				}
				else if(mesh.isBorder(n)){
					A[n][n] = 1;
					b[n] = 0; // condicao de contorno de dirichet homogenena
				}
				else if(mesh.isBorder(m)){
					b[n] = b[n] - K*0; // condicao de contorno de dirichet homogenena
				}
				// if(b[m] != 0)
					// cout << b[m] << endl;
			}
		}
	}

	cout << "#MaxIt: " << GaussSeidel(&A,&x,&b, 1e-5,500) << endl;

	// Resultados
	// funcao forca
	for (int i = 0; i < mesh.nx; ++i){
		for (int j = 0; j < mesh.ny; ++j){
			int n = j + mesh.ny*i;
			fforce << mesh.nodes[n].show() << "\t" << fun(mesh.nodes[n][0],mesh.nodes[n][1]) << endl;
		}
		fforce << endl;
	}

	// resultado
	for (int i = 0; i < mesh.nx; ++i){
		for (int j = 0; j < mesh.ny; ++j){
			int n = j + mesh.ny*i;
			foutput << mesh.nodes[n].show() << "\t" << x[n] << endl;
		}
		foutput << endl;
	}

	fforce.close();
	foutput.close();

	return 0;

}