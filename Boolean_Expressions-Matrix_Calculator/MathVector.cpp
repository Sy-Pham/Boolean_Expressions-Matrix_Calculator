#include "MathVector.h"
#include <iostream>
using namespace std;

MathVector::MathVector() {}

// input: vector<double> src
// usage: initialize the MathVector class from vector<double>
MathVector::MathVector(vector<double> src)
{
	(this->val) = src;
}

MathVector::~MathVector()
{
}

// input: const MathVector& other
// output: MathVector&
// usage: perform addition on 2 vector and return the 
// object after the addition
MathVector& MathVector::add(const MathVector& other) {
	int sizeSrc = (this->val).size();
	int sizeOther = (other.val).size();

	// so sanh chieu cua hai vector
	if (sizeSrc != sizeOther) {
		throw string("Hai vector khong co cung chieu");
	}
	
	// thuc hien phep cong vector
	for (int i = 0; i < sizeSrc; i++) {
		(this->val)[i] += (other.val)[i];
	}

	return *this;
}

// input: double scalar
// output: MathVector&
// usage: perform multiplication on 2 vector
MathVector& MathVector::multiply(double scalar) {
	int size = (this->val).size();

	for (int i = 0; i < size; i++) {
		(this->val)[i] *= scalar;
	}

	return *this;
}

// input: void
// output: void
// usage: print the value of the vector on the screen
void MathVector::output() {
	int size = val.size();

	cout << "(";
	for (int i = 0; i < size; i++) {
		if (i == (size - 1)) {
			cout << val[i];
			break;
		}
		cout << val[i] << ", ";
	}
	cout << ")";
}
