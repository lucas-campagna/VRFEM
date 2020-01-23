#include <Vector.h>

using namespace std;

Vector::Vector() : Vector(0){}
Vector::Vector(int dim) : dim(dim){x.resize(dim,0);}
Vector::Vector(double *vec,int n): dim(n){x.resize(dim);for (int i = 0; i < n; ++i) x[i] = vec[i];}
Vector::Vector(std::initializer_list<double> vec) : dim(vec.size()){
	std::initializer_list<double>::iterator it = vec.begin();

	x.resize(dim,0);


	for(int i = 0; i < dim; i++)
		x[i] = *(it++);

}


void Vector::reset(){x.resize(dim,0);}
void Vector::resize(int pdim){dim = pdim; x.resize(pdim,0);}

double Vector::norm(){return sqrt(dot(*this));}


double Vector::dot(Vector vec){return ((*this) * vec).sum();}


Vector Vector::vec(Vector vec){
	assert(dim == vec.dim);

	Vector myvec(3);
	if(dim == 2){
		myvec[0] = 0;
		myvec[1] = 0;
		myvec[2] = x[0]*vec[1] - x[1]*vec[0];
	}
	if(dim == 3){
		myvec[0] = x[1]*vec[2] - x[2]*vec[1];
		myvec[1] = x[2]*vec[0] - x[0]*vec[2];
		myvec[2] = x[0]*vec[1] - x[1]*vec[0];
	}
	return myvec;
}

double Vector::sum(){
	double sum = 0.0;
	for (int i = 0; i < dim; ++i)
		sum += x[i];
	return sum;
}

Vector Vector::operator* (double a){
	Vector myvec(dim);
	for (int i = 0; i < dim; ++i)
		myvec[i] = x[i] * a;
	return myvec;
}

Vector Vector::operator/ (double a){
	Vector myvec(dim);
	for (int i = 0; i < dim; ++i)
		myvec[i] = x[i] / a;
	return myvec;
}

Vector Vector::operator+ (double a){
	Vector myvec(dim);
	for (int i = 0; i < dim; ++i)
		myvec[i] = x[i] + a;
	return myvec;
}

Vector Vector::operator- (double a){	
	return *this + (-a);
}


Vector Vector::operator+ (Vector vec){
	assert(dim == vec.dim);

	Vector myvec(dim);
	for (int i = 0; i < dim; ++i)
		myvec[i] = x[i] + vec[i];
	return myvec;
}


Vector Vector::operator- (Vector vec){
	return *this + (vec * (-1));
}

Vector Vector::operator* (Vector vec){
	assert(dim == vec.dim);

	Vector myvec(dim);
	for (int i = 0; i < dim; ++i)
		myvec[i] = x[i] * vec[i];
	return myvec;
}

Vector Vector::operator/ (Vector vec){
	assert(dim == vec.dim);

	Vector myvec(dim);
	for (int i = 0; i < dim; ++i)
		myvec[i] = x[i] / vec[i];
	return myvec;
}

void Vector::operator+= (double a){
	for (int i = 0; i < dim; ++i)
		x[i] += a;
}

void Vector::operator-= (double a){
	for (int i = 0; i < dim; ++i)
		x[i] -= a;
}

void Vector::operator*= (double a){
	for (int i = 0; i < dim; ++i)
		x[i] *= a;
}

void Vector::operator/= (double a){
	for (int i = 0; i < dim; ++i)
		x[i] /= a;
}

void Vector::operator+= (Vector vec){
	assert(dim == vec.dim);

	for (int i = 0; i < dim; ++i)
		x[i] += vec[i];
}

void Vector::operator-= (Vector vec){
	assert(dim == vec.dim);

	for (int i = 0; i < dim; ++i)
		x[i] -= vec[i];
}

void Vector::operator*= (Vector vec){
	assert(dim == vec.dim);

	for (int i = 0; i < dim; ++i)
		x[i] *= vec[i];
}

void Vector::operator/= (Vector vec){
	assert(dim == vec.dim);

	for (int i = 0; i < dim; ++i)
		x[i] /= vec[i];
}

void Vector::operator= (Vector vec){
	assert(dim == vec.dim);

	for (int i = 0; i < dim; ++i)
		x[i] = vec[i];
}

void Vector::operator= (std::initializer_list<double> vec){
	assert(dim == vec.size());

	std::initializer_list<double>::iterator it = vec.begin();

	for (int i = 0; i < dim; ++i){
		x[i] = *(it++);
	}
}

void Vector::operator= (double a){
	for (int i = 0; i < dim; ++i)
		x[i] = a;
}

void Vector::operator= (double a[]){
	for (int i = 0; i < dim; ++i)
		x[i] = a[i];	
}

// void Vector::operator< (Vector vec){
// 	(*this) = vec;
// }

int Vector::operator== (Vector vec){
	if(dim != vec.dim)
		return 0;

	for (int i = 0; i < dim; ++i)
		if (x[i] != vec[i])
			return 0;
	return 1;
}
int Vector::operator!= (Vector vec){
	return ! (*this == vec);
}

// string Vector::operator() (){
string Vector::show(){
	string str;
	for (int i = 0; i < dim-1; ++i)
		str += to_string(x[i]) + " ";
	str += to_string(x[dim-1]);
	return str;
}

double & Vector::operator[] (int i){return x[i];};