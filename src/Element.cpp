#include <Element.h>

using namespace std;


// extern std::vector<Vector> node; // imported from main.cpp

Element::Element(int nNodes) : nNodes(nNodes) {map.resize(nNodes);}

Element::Element( std::vector<int> map, std::vector<Vector> *nodes) : pNodes(nodes), map(map), nNodes(map.size()) {
	// area = 0;
	calc_area();
}
// Element::Element( int first_map, int last_map){
// 	assert(first_map < last_map);

// 	nNodes = last_map - first_map;
// 	map.resize(nNodes,0);

// 	for (int i = 0; i < nNodes; ++i)
// 		map[i] = first_map + i;
// }

void Element::set_pNodes(std::vector<Vector> *nodes){pNodes = nodes;}

void Element::calc_area(){
	if(map.size() == 2)
		area = ((*pNodes)[map[1]] - (*pNodes)[map[0]]).norm();
	else if(map.size() == 3){
		Vector v1 = (*pNodes)[map[0]],
		v2 = (*pNodes)[map[1]],
		v3 = (*pNodes)[map[2]],
		aux = v1;

		aux = v1;
		v1 = v2 - v1;
		v2 = v3 - aux;

		area = v1.vec(v2).norm()*0.5;
	}// implementar para mais casos

}

Vector Element::nodeVec(int i){return (*pNodes)[map[i]];}


Poly1d Element::shapef(int i){
	int dim = (*pNodes)[0].dim;


	Matrix A(nNodes,dim);
	for(int j = 0; j < map.size(); j++)
		A.row((*pNodes)[map[j]],j); // monta matriz com coordenada dos pontos em cada linha
	A.to_square();

	return A.udet(i,dim)/A.det();
}

int & Element::operator[](int i){return map[i];}

double Element::integrate(double (*fun)(double,double), int k, int nx, int ny){
	/*
	Calcula integral da funcao parametro "fun" no dominio especificado pelos nós do elemento
	Implementado apenas para elementos triangulares.
	*/ 

	Vector v1 = nodeVec(0),
		   v2 = nodeVec(1),
		   v3 = nodeVec(2);

	Vector b1(v1.dim), b2(v1.dim); // basis vectors

	double integral = 0;
	double Ab;

	b1 = (v2 - v1)/(nx-1.);
	b2 = (v3 - v1)/(ny-1.);

	Ab = b1.vec(b2).norm()/(2.0*(nx-1)*(ny-1)); // area da base triangular

	Poly1d p = shapef(k);

	for (int i = 0; i < nx-1; ++i){
		Vector x1(b1.dim),x2(b1.dim),x3(b1.dim);
		for (int j = 0; j < ny-i-1; ++j){
			x1 = b1 * i     + b2 * j     + v1;
			x2 = b1 * (i+1) + b2 * j     + v1;
			x3 = b1 * i     + b2 * (j+1) + v1;

			double h = (fun(x1[0],x1[1])*p(x1[0],x1[1]) + fun(x2[0],x2[1])*p(x2[0],x2[1]) + fun(x3[0],x3[1])*p(x3[0],x3[1]))/3.0; // media das alturas em cada no

			integral += Ab*h;
		}
		for (int j = 0; j < ny-i-2; ++j){
			x1 = b1 * (i+1) + b2 * j     + v1;
			x2 = b1 * i     + b2 * (j+1) + v1;
			x3 = b1 * (i+1) + b2 * (j+1) + v1;

			double h = (fun(x1[0],x1[1])*p(x1[0],x1[1]) + fun(x2[0],x2[1])*p(x2[0],x2[1]) + fun(x3[0],x3[1])*p(x3[0],x3[1]))/3.0; // media das alturas em cada no

			integral += Ab*h;
		}
	}
		return integral;
}