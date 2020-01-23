#ifndef MATRIX
#define MATRIX

#include <Vector.h>
#include <vector>
#include <Poly1d.h>
#include <initializer_list>
#include <cmath>
#include <cstdlib>

class Matrix{
	// std::vector<std::vector<double>> data;
	double **data;

	// struct str_data{
	// 	double *data;
	// 	double & operator[](int i){};
	// } *data;

	public:
		int ncols, nrows;
		Matrix(int);
		Matrix(int,int);
		Matrix(std::initializer_list<Vector>);
		Matrix(std::initializer_list<double>,int,int);

		void resize(int,int);
		void resize(int);
		void reset();

		void zeros();
		void ones();

		void show();

		Vector row(int);
		void row(Vector, int);

		Vector col(int);
		void col(Vector, int);

		Vector diag(int k = 0);
		void diag(Vector, int);

		double* & operator[](int);
		// void operator[](int);

		double det();
		Poly1d udet(int i, int dim = -1);
		double xdet(int, int);
		void t();
		double trace();
		void to_square(double val = 1);

		Matrix operator*(Matrix);
		Vector operator*(Vector);

		void operator=(std::initializer_list<double>);

		void inverse();
};

#endif