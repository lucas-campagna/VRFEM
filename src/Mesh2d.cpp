#include <Mesh2d.h>

using namespace std;

Mesh2d::Mesh2d(int x0, int y0, int x1, int y1, int nx, int ny) : x0(x0), y0(y0), x1(x1), y1(y1), nx(nx), ny(ny){
	Vector aux(2);

	nodes.resize(nx*ny,2);

	hx = (double) (x1 - x0)/(nx - 1);
	hy = (double) (y1 - y0)/(ny - 1);


	
	for (int i = 0; i < nx; ++i)
		for (int j = 0; j < ny; ++j){
			aux[0] = j*hx + x0;
			aux[1] = i*hy + y0;
			nodes[j + nx*i].reset(); // necessario para resetar os endereços de memoria dos ponteiros.
			nodes[j + nx*i] = aux;
		}

	// build triangular elements

	elements.resize((nx-1)*(ny-1)*2,3);

	for (int j = 0; j < ny-1; ++j)
		for (int i = 0; i < nx-1; ++i){

			int ei = 2*(i + (nx-1)*j); // element index
			int ni = i + nx*j; // node index

			elements[ei][0] = ni;
			elements[ei][1] = ni+nx;
			elements[ei][2] = ni+1;

			elements[ei].set_pNodes(&nodes);
			elements[ei].calc_area();

			elements[ei+1][0] = ni+1;
			elements[ei+1][1] = ni+nx;
			elements[ei+1][2] = ni+nx+1;

			elements[ei+1].set_pNodes(&nodes);
			elements[ei+1].calc_area();
		}
}

int Mesh2d::isBorder(int i){
	/*
	verifica se o indice o nó de indice 'i' está na borda
	*/
	if(i >= 0 && i < nx)
		return 1;
	if(i >= nx*(ny-1) && i < nx*ny)
		return 1;
	if(i%nx == 0 || i%nx == nx-1)
		return 1;
	return 0;
}