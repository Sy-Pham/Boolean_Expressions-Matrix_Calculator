#pragma once
#include <vector>
using namespace std;

class Matrix {
private:
	vector<vector<double>> val;
	vector<vector<double>> L;
	vector<vector<double>> U;
	int rankValue;
	double det;
public: 
	Matrix();
	Matrix(vector<vector<double>>);
	Matrix(const Matrix&);
	~Matrix();

	double determinant();
	const Matrix transpose();
	const Matrix inverse();
	const Matrix multiply(const Matrix&);
	int rank();
	const Matrix solve(vector<vector<double>>);
};

void LUDecomposition(vector<vector<double>>, vector<vector<double>>&, vector<vector<double>>&);
const vector<vector<double>> gaussElimination(const vector<vector<double>>&);