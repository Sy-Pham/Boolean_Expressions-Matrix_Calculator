#include "Matrix.h"
#include <iostream>
using namespace std;

// usage: initialize the val matrix, the lower triangle matrix L, the upper triangle matrix U
// the rank of the matrix and the determinant
Matrix::Matrix() {
	val = vector<vector<double>>({ {} });
	L = vector<vector<double>>({ {} });
	U = vector<vector<double>>({ {} });
	rankValue = -1;
	det = FLT_MIN;
}

// input: vector<vector<double>> src
// usage: initialize the val matrix, the lower triangle matrix L, the upper triangle matrix U
// the rank of the matrix and the determinant
Matrix::Matrix(vector<vector<double>> src) {
	val = src;
	L = vector<vector<double>>({ {} });
	U = vector<vector<double>>({ {} });
	rankValue = -1;
	det = FLT_MIN;
}

// input: const Matrix& other
// usage: copy the val matrix, the lower triangle matrix L, the upeer triangle matrix U
// the rank of the matrix and the determinant
Matrix::Matrix(const Matrix& other) {
	val = other.val;
	L = other.L;
	U = other.U;
	rankValue = other.rankValue;
	det = other.det;
}

Matrix::~Matrix() {}

// input: void
// output: the determinant value
// usage: to calculate the determinant of the square matrix
double Matrix::determinant() {
	// check if the determinant have been calculated before
	// if so return the existing value
	if (det > FLT_MIN)
		return det;

	int rowSrc = val.size();
	int colSrc = val[0].size();

	// check for square matrix
	if (rowSrc != colSrc) {
		throw string("Khong the tinh dinh thuc vi ma tran khong vuong");
	}

	// crout algorithm - LU decomposition - Reference: Wikipedia
	int i, j, k, n = rowSrc;
	double sum = 0;

	try {
		LUDecomposition(val, L, U);
	}
	catch (string e) {
		cout << "Loi: " << e << endl;
	}

	double detL = 1;
	for (i = 0; i < n; i++) {
		detL *= L[i][i];
	}
	return detL;
}

// input: void
// output: const Matrix
// usage: create a new transpose matrix of the original matrix
const Matrix Matrix::transpose() {
	int rowSrc = val.size();
	int colSrc = val[0].size();

	// the transpose matrix has numbers of original matrix column as its numbers of rows
	// and numbers of original matrix rows as its numbers of columns
	vector<double> tempCol(rowSrc, 0);
	vector<vector<double>> tempRow(colSrc, tempCol);

	// make a copy from the val matrix
	for (int i = 0; i < rowSrc; i++) {
		for (int j = 0; j < colSrc; j++) {
			tempRow[j][i] = val[i][j];
		}
	}

	Matrix result(tempRow);
	return result;
}

// input: void
// output: an inverse matrix of the original
// usage: use the LU decomposition like in the crout algorithm
// find the inverse of both the L matrix and the U matrix and multiply the two matrix together
const Matrix Matrix::inverse() {
	int rowSrc = val.size();
	int colSrc = val[0].size();

	// check if the matrix is a square matrix
	if (rowSrc != colSrc) {
		throw string("Khong the tinh dinh thuc vi ma tran khong vuong");
	}

	// check if the matrix has a non-zero determinant
	if ((this->determinant() == 0)) {
		throw string("Ma tran khong co ma tran nghich dao");
	}

	// n is the variable that holds the row's size of the matrix
	int n = rowSrc;
	double sum = 0;

	// LU Decomposition
	LUDecomposition(val, L, U);

	// using back subsitution to find the inverse of the matrix L and U
	// back subsitution is a subsituting each of the equations to solve the triangle matrix
	vector<double> temp(n, 0);
	vector<vector<double>> backSubL(n, temp);
	vector<vector<double>> backSubU(n, temp);
	vector<vector<double>> unitMatrix(n, temp);

	// initialize a unit matrix
	for (int i = 0; i < n; i++) {
		unitMatrix[i][i] = 1;
	}

	// j is an index for each of the column of the result matrix we need to find
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			sum = 0;

			for (int k = 0; k < i; k++) {
				sum += L[i][k] * backSubL[k][j];
			}

			backSubL[i][j] = (unitMatrix[i][j] - sum) / L[i][i];
		}
	}

	for (int j = 0; j < n; j++) {
		for (int i = n - 1; i >= 0; i--) {
			sum = 0;

			for (int k = i; k < n; k++) {
				sum += U[i][k] * backSubU[k][j];
			}

			backSubU[i][j] = (unitMatrix[i][j] - sum) / U[i][i];
		}
	}

	Matrix result(backSubL);
	Matrix result2(backSubU);
	return result2.multiply(result);
}

// input: const Matrix& other
// output: const Matrix
// usage: return the product of two matrix
const Matrix Matrix::multiply(const Matrix& other) {
	int rowSrc = (this->val).size();
	int colSrc = (this->val)[0].size();
	int rowOther = (other.val).size();
	int colOther = (other.val)[0].size();

	// initialize a 2 dimensional vector, with row = rowSrc, col = colSrc
	vector<double> temp(colOther, 0);
	vector<vector<double>> result(rowSrc, temp);

	// check if the two matrix can be multiplied
	if (colSrc != rowOther) {
		throw string("Khong the thuc hien phep nhan hai ma tran");
	}

	// multiply the matrix by each of the row and column
	for (int i = 0; i < rowSrc; i++) {
		for (int j = 0; j < colOther; j++) {
			double temp = 0;
			for (int k = 0; k < colSrc; k++) {
				temp += val[i][k] * other.val[k][j];
			}
			result[i][j] = temp;
		}
	}

	Matrix matrixResult(result);
	return matrixResult;
}

// input: void
// output: the rank value of the matrix
// usage: use the gausse elimination to reduce the matrix and 
// then count the non-zero row and return the value
int Matrix::rank() {
	// check if the rankValue have been calculated before
	// if so return the existing value
	if (rankValue != -1)
		return rankValue;

	vector<vector<double>> result = gaussElimination(val);
	int rowSize = result.size();
	int colSize = result[0].size();
	int temp = rowSize;
	bool emptyRow;
	
	for (int i = rowSize - 1; i >= 0; i--) {
		emptyRow = true;
		for (int j = 0; j < colSize; j++) {
			if (result[i][j] > (0.000000001)) {
				emptyRow = false;
				break;
			}
		}

		if (emptyRow == true) {
			temp--;
		}
	}
	rankValue = temp;

	return rankValue;
}

// input: vector<vector<double>>& augmentValue
// output: const Matrix
// usage: solve the system of equations which has the numbers of variable
// equal to the number of equations.
const Matrix Matrix::solve(vector<vector<double>>& augmentValue) {
	// initialize a coefficient matrix
	Matrix coeffMatrix(*this);
	Matrix result;

	// initialize the right hand matrix
	// example
	// x + 2y = 2
	// 3x + y = 1
	// [[2],[1]] is the rightHandMatrix
	// [[1, 2], [3, 1]] is the coefficient matrix
	// [[1,2, 2], [3, 1, 1]] is the augmented matrix
	Matrix rightHandMatrix(augmentValue);

	vector<vector<double>> temp(val);

	// create an augmented matrix
	for (int i = 0; i < augmentValue.size(); i++) {
		temp[i].push_back(augmentValue[i][0]);
	}

	Matrix augmentMatrix(temp);

	// calculate the rank of the coefficient matrix
	int coeffMatrixRank = coeffMatrix.rank();

	// calculate the rank of the coefficient matrix
	int augmentMatrixRank = augmentMatrix.rank();

	// compare the rank of the coefficient matrix and the augment matrix
	if (coeffMatrixRank < augmentMatrixRank) {
		throw string("He phuong trinh da cho vo nghiem");
	}
	else if (coeffMatrixRank > augmentMatrixRank) {
		throw string("He phuong trinh da cho co vo so nghiem");
	}
	else {
		// inverse the coefficient matrix
		result = coeffMatrix.inverse();

		// and multiply it with the right hand matrix
		result = result.multiply(rightHandMatrix);
	}

	return result;
}

// input: void
// output: void
// usage: output the Matrix to screen
void Matrix::output() {
	int dimensionX = val.size();
	int dimensionY = val[0].size();

	cout << "(";
	for (int i = 0; i < dimensionX; i++) {
		if (i == 0)
			cout << " (";
		else 
			cout << "  (";

		for (int j = 0; j < dimensionY; j++) {
			if (j == (dimensionY - 1)) {
				cout << val[i][j];
				break;
			}
			cout << val[i][j] << ", ";
		}

		if (i == (dimensionX - 1))
			cout << ") ";
		else
			cout << ")," << endl;
	}
	cout << ")";
}

// input: vector<vector<double>> A, vector<vector<double>>& L, vector<vector<double>>& U
// output: void
// usage: decompose the given square matrix A into 2 triangle matrix:
// the lower triangle matrix L and the upper triangle matrix U
void LUDecomposition(vector<vector<double>> A, vector<vector<double>> &L, vector<vector<double >> &U) {
	if (L.size() > 1 && U.size() > 1)
		return;

	vector<double> temp(A.size(), 0);
	L = vector<vector<double>>(A.size(), temp);
	U = vector<vector<double>>(A.size(), temp);
	
	int i, j, k;
	double sum = 0;
	int n = A.size();
	
	for (j = 0; j < n; j++) {
		
		// in this loop, the i variable is the row of L
		// j is the column of U
		// this loop is used to calculate the member of L
		for (i = 0; i < n; i++) {
			sum = 0;

			// find the product of the i-th row of L with the j-th column of U
			for (k = 0; k < j; k++) {
				sum = sum + L[i][k] * U[k][j];
			}
			L[i][j] = A[i][j] - sum;
		}

		// in this loop, the j variable is the row of L
		// i is the column of U
		// this loop is used to calculate the member of U
		for (i = 0; i < n; i++) {
			sum = 0;
			for (k = 0; k < j; k++) {
				sum = sum + L[j][k] * U[k][i];
			}
			// if there are a member in the diagonal line of the lower matrix L
			// has the value 0 then throw errror
			if (L[j][j] == 0) {
				throw string("Ma tran co dinh thuc bang 0");
			}
			U[j][i] = (A[j][i] - sum) / L[j][j];
		}
	}
}

// input: const vector<vector<double>> src
// output: const vector<vector<double>>
// usage: reduce the matrix src to echelon form
const vector<vector<double>> gaussElimination(const vector<vector<double>>& src) {
	vector<vector<double>> result = src;
	int row = result.size();
	int col = result[0].size();

	int pivotRow = 0;
	int pivotCol = 0;
	int i_max = 0;

	while (pivotRow < row && pivotCol < col) {
		i_max = pivotRow;
		for (int i = pivotRow; i < row; i++) {
			if (abs(result[i][pivotRow]) > abs(result[i_max][pivotRow])) {
				i_max = i;
			}
		}

		if (result[i_max][pivotCol] == 0) {
			pivotCol++;
		}
		else {
			swap(result[pivotRow], result[i_max]);

			for (int i = pivotRow + 1; i < row; i++) {
				double f = (double)result[i][pivotCol] / result[pivotRow][pivotCol];

				result[i][pivotCol] = 0;

				for (int j = pivotCol + 1; j < col; j++) {
					result[i][j] = result[i][j] - result[pivotRow][j] * f;
				}
			}

			pivotCol++;
			pivotRow++;
		}
	}

	return result;
}