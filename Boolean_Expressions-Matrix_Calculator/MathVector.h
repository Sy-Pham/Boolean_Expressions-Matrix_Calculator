#pragma once
#include <vector>
using namespace std;

class MathVector
{
private:
	vector<double> val;
public:
	MathVector();
	MathVector(vector<double>);
	~MathVector();
	MathVector& add(const MathVector&);
	MathVector& multiply(double);
};

