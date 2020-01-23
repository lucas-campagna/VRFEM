#ifndef VECTOR
#define VECTOR

#include <cmath>
#include <string>
#include <cassert>
#include <vector>
#include <initializer_list>
#include <iostream>

class Vector{
		std::vector<double> x; 
	public:
		int dim; 
		Vector();
		Vector(int dim);
		Vector(double *vec,int n);
		Vector(std::initializer_list<double>);
		void reset();
		void resize(int);
		double sum();
		double norm();
		double dot(Vector);
		Vector vec(Vector);


		Vector operator+ (double);
		Vector operator- (double);
		Vector operator* (double);
		Vector operator/ (double);

		Vector operator+ (Vector);
		Vector operator- (Vector);
		Vector operator* (Vector);
		Vector operator/ (Vector);

		void operator+= (double);
		void operator-= (double);
		void operator*= (double);
		void operator/= (double);

		void operator+= (Vector);
		void operator-= (Vector);
		void operator*= (Vector);
		void operator/= (Vector);

		void operator= (std::initializer_list<double>);
		void operator= (Vector);
		void operator= (double);
		void operator= (double *);
		std::string show();
		// std::string operator() ();

		// void operator< (Vector);
		int operator== (Vector);
		int operator!= (Vector);
		double & operator[] (int);

};

#endif