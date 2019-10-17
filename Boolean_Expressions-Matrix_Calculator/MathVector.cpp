#include "MathVector.h"
#include <iostream>
using namespace std;

MathVector::MathVector() {}

MathVector::MathVector(vector<double> src)
{
	(this->val) = src;
}

MathVector::~MathVector()
{
}

MathVector& MathVector::add(const MathVector& other) {
	int sizeSrc = (this->val).size();
	int sizeOther = (other.val).size();

	// so sanh chieu cua hai vector
	if (sizeSrc != sizeOther) {
		throw ("Hai vector khong co cung chieu");
	}
	
	// thuc hien phep cong vector
	for (int i = 0; i < sizeSrc; i++) {
		(this->val)[i] += (other.val)[i];
	}

	return *this;
}

MathVector& MathVector::multiply(double scalar) {
	int size = (this->val).size();

	for (int i = 0; i < size; i++) {
		(this->val)[i] *= scalar;
	}

	return *this;
}
