#include <Matrix.h>

#include <iostream>
using namespace std;


Matrix::Matrix(int order) : Matrix(order,order){}

Matrix::Matrix(int nrows, int ncols) : nrows(nrows), ncols(ncols){
	resize();
}


Matrix::Matrix(std::initializer_list<Vector> ivlist) : nrows(ivlist.size()), ncols(ivlist.begin()->dim){

	std::initializer_list<Vector>::iterator it = ivlist.begin();

	resize();

	for (int i = 0; i < nrows; ++i){
		for (int j = 0; j < ncols; ++j)
			data[i][j] = ((Vector) *it)[j];

		it++;
	}

}

Matrix::Matrix(std::initializer_list<double> ivlist, int nrows, int ncols) : nrows(nrows), ncols(ncols){
	std::initializer_list<double>::iterator it = ivlist.begin();
	assert(nrows*ncols == ivlist.size());
	resize();
	for (int i = 0; i < nrows; ++i)
		for (int j = 0; j < ncols; ++j){
			data[i][j] = (double) *it;
			it++;
		}
}

void Matrix::resize(int nrows, int ncols){
	nrows = nrows;
	ncols = ncols;
	resize();
}

void Matrix::resize(int order){
	resize(order, order);
}

void Matrix::resize(){
	data = (double **) malloc(sizeof(double *) * nrows);
	
	for (int i = 0; i < nrows; ++i)
		data[i] = (double *) malloc(sizeof(double) * ncols);
		
}

void Matrix::zeros(){
	for(int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; ++j)
			data[i][j] = 0;
}

void Matrix::ones(){
	for(int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; ++j)
			data[i][j] = 1;
}

void Matrix::show(){
	for (int i = 0; i < nrows; ++i){
		for (int j = 0; j < ncols; ++j)
			std::cout << data[i][j] << "\t";
		std::cout << std::endl;
	}
}


Vector Matrix::row(int i){
	Vector vec(ncols);
	for(int j = 0; j < ncols; j++)
		vec[j] = data[i][j];
	return vec;
}

void Matrix::row(Vector vec, int i){
	for(int j = 0; j < ncols; j++)
		data[i][j] = vec[j];
}

Vector Matrix::col(int i){
	Vector vec(nrows);
	for(int j = 0; j < nrows; j++)
		vec[j] = data[j][i];
	return vec;
}

void Matrix::col(Vector vec, int i){
	for(int j = 0; j < nrows; j++)
		data[j][i] = vec[j];
}

Vector Matrix::diag(int k){
	assert(nrows == ncols);
	Vector vec(nrows);
	if(k > 0)
		for(int j = 0; j < nrows - k; j++)
			vec[j] = data[j][j + k];
	else
		for(int j = 0; j < nrows - k; j++)
			vec[j] = data[j + k][j];
	return vec;
}

void Matrix::diag(Vector vec, int k){
	assert(nrows == ncols && vec.dim == nrows - k);
	if(k > 0)
		for(int j = 0; j < nrows - k; j++)
			data[j][j+k] = vec[j];
	else
		for(int j = 0; j < nrows - k; j++)
			data[j+k][j] = vec[j];
}


Poly1d Matrix::udet(int i, int dim){
	/*
	Retorna polinomio calculado pelo determinante da matriz com os ultimos 'dim' elementos da linha 'i' sendo variaveis
	Exemplo: considere a matriz abaixo

	| 1 x1 y1 |
	| 1 x2 y2 |
	| 1 x3 y3 |

	A chamada desta funcao para esta matriz com i = 1 e dim = 2 sera o polinomio calculado pelo determinante de

	| 1 x1 y1 |
	| 1 x  y  | <- i = 1
	| 1 x3 y3 |
	    ^
		|- dim = 2

	Sendo x e y variaveis do polinomio.
	*/
	if(dim == -1) dim = ncols;
	assert(ncols >= dim);

	double b = 0;
	Vector a(dim);

	for (int j = 0; j < ncols - dim; ++j)
		b += data[i][j]*xdet(i,j)*pow(-1,i+j);

	for (int j = ncols - dim; j < ncols; ++j)
		a[j - (ncols - dim)] = xdet(i,j)*pow(-1,i+j);

	return Poly1d(a,b);
}

double Matrix::det(){
	assert(nrows == ncols);

	if(nrows == 1 && ncols == 1)
		return data[0][0];

	int i  = 0;
	double det = 0;
	for (int j = 0; j < ncols; ++j)
		det += data[i][j]*xdet(i,j)*pow(-1,i+j);
	return det;
}

double Matrix::xdet(int i, int j){ // determinante da matriz excluidas a linha i e coluna j
	Matrix maux(nrows-1,ncols-1);
	int iii = 0;
	int jjj;

	for (int ii = 0; ii < i; ++ii){
		jjj = 0;
		for (int jj = 0; jj < j; ++jj){
			maux[iii][jjj] = data[ii][jj];
			jjj++;
		}

		for (int jj = j+1; jj < ncols; ++jj){
			maux[iii][jjj] = data[ii][jj];
			jjj++;
		}
		iii++;
	}

	for (int ii = i+1; ii < nrows; ++ii){
		jjj = 0;
		for (int jj = 0; jj < j; ++jj){
			maux[iii][jjj] = data[ii][jj];
			jjj++;
		}

		for (int jj = j+1; jj < ncols; ++jj){
			maux[iii][jjj] = data[ii][jj];
			jjj++;
		}
		iii++;
	}
	return maux.det();
}

void Matrix::t(){
	if(nrows != ncols){
	
	Matrix maux(ncols,nrows);

	for (int i = 0; i < nrows; ++i)
		maux.col(row(i),i);
		(*this) = maux;
	}else{
		double aux;
		for (int i = 0; i < nrows; ++i)
			for (int j = i+1; j < ncols; ++j){
				aux = data[i][j];
				data[i][j] = data[j][i];
				data[j][i] = aux;
			}
	}

}

double Matrix::trace(){
	assert(nrows == ncols);

	double trace = 0;
	for(int i = 0; i < nrows; i++)
		trace += data[i][i];
	return trace;
}

double* & Matrix::operator[] (int i){return data[i];}

void Matrix::to_square(double val){
	/*
	Set matrix to square of higest order setting val in the new empty elements
	*/
	if(nrows == ncols) return;
	
	int order = (nrows > ncols? nrows : ncols);

	Matrix maux(order);
	maux.ones();

	if(nrows == order)
	for (int i = 0; i < nrows; ++i)
		for (int j = 0; j < ncols; ++j)
			maux[i][j + order - ncols] = data[i][j];
	else
		for (int i = 0; i < nrows; ++i)
			for (int j = 0; j < ncols; ++j)
				maux[i + order - nrows][j] = data[i][j];


	nrows = ncols = order;
	resize(order);
	for (int i = 0; i < nrows; ++i)
		for (int j = 0; j < ncols; ++j)
			data[i][j] = maux[i][j];
}

void Matrix::inverse(){
	/*
	Calcula matriz inversa 
	*/
}

Matrix Matrix::operator*(Matrix A){
	Matrix B(A.nrows,A.ncols);
	for (int i = 0; i < A.nrows; ++i){
		for (int j = 0; j < A.ncols; ++j){
			B[i][j] += (row(i)*A.col(j)).sum();
		}
	}
	return B;
}

Vector Matrix::operator*(Vector v){
	Vector w(v.dim);
	for (int i = 0; i < v.dim; ++i){
		w[i] = (row(i)*v).sum();
	}
	return w;
}

void Matrix::operator=(std::initializer_list<double> A){
	std::initializer_list<double>::iterator it = A.begin();
	
	for (int i = 0; i < nrows; ++i)
		for (int j = 0; j < ncols; ++j){
			data[i][j] = (double) *it;
			it++;
		}		
}