#include "MathVector.h"
#include "Matrix.h"

void main1() {
	/*vector<double> val = { 1, 2, 3.5, 4.6 };
	vector<double> val2 = { 10.1, 10.5, 4.5, 6 };
	MathVector v(val);
	MathVector v2(val2);

	v.add(v2);
	int scalar = 10;
	v2.multiply(scalar);
*/

	vector<vector<double>> val = { {1, 1, 1}, {5, 3, 2}, {0, 1, -1} };
	Matrix m3(val);
	vector<vector<double>> rightHandValue = { {25}, {0}, {6} };
	Matrix m4 = m3.solve(rightHandValue);

	vector<vector<double>> testGauss = { {1, 1, 1, 25}, {5, 3, 2, 0}, {0, 1, -1, 6} };
	Matrix m5(gaussElimination(testGauss));


	/*vector<vector<double>> test1 = { {5}, {6} };
	vector<vector<double>> test2 = { {1, 3}, {3, 4} };
	Matrix m4(test2);
	m4 = m4.inverse();
	m4 = m4.multiply(Matrix(test1));*/

}