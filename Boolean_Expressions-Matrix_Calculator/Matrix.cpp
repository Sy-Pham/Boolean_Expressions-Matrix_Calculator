#include "Matrix.h"

Matrix::Matrix() {
	val = vector<vector<double>>({ {} });
	L = vector<vector<double>>({ {} });
	U = vector<vector<double>>({ {} });
	rankValue = -1;
	det = FLT_MIN;
}

Matrix::Matrix(vector<vector<double>> src) {
	val = src;
	L = vector<vector<double>>({ {} });
	U = vector<vector<double>>({ {} });
	rankValue = -1;
	det = FLT_MIN;
}

Matrix::Matrix(const Matrix& other) {
	val = other.val;
	L = other.L;
	U = other.U;
	rankValue = other.rankValue;
	det = other.det;
}

Matrix::~Matrix() {}

// input: khong
// output: gia tri dinh thuc cua ma tran vuong
// 
double Matrix::determinant() {
	if (det > FLT_MIN)
		return det;

	int rowSrc = val.size();
	int colSrc = val[0].size();

	// kiem tra ma tran vuong
	if (rowSrc != colSrc) {
		throw ("Khong the tinh dinh thuc vi ma tran khong vuong");
	}

	// thuat toan crout - ung dung LU decomposition - tham khao: Wikipedia
	int i, j, k, n = rowSrc;
	double sum = 0;

	LUDecomposition(val, L, U);

	// A = LU => det(A) = det(L) * det(U)
	// ma det(U) = 1 vi duong cheo chinh cua U toan so 1
	// => det(A) = det(L)
	double detL = 1;
	for (i = 0; i < n; i++) {
		detL *= L[i][i];
	}
	return detL;
}

const Matrix Matrix::transpose() {
	int rowSrc = val.size();
	int colSrc = val[0].size();

	// ma tran chuyen vi co so cot = so hang ban dau va so hang = so cot ban dau
	vector<double> tempCol(rowSrc, 0);
	vector<vector<double>> tempRow(colSrc, tempCol);

	// copy tu mang hai chieu val qua tempRow
	for (int i = 0; i < rowSrc; i++) {
		for (int j = 0; j < colSrc; j++) {
			tempRow[j][i] = val[i][j];
		}
	}

	Matrix result(tempRow);
	return result;
}

// cach lam la dung LU decompostion giong trong crout algorithm 
// tim nghich dao cua hai ma tran L va U roi nhan ca hai lai voi nhau
const Matrix Matrix::inverse() {
	int rowSrc = val.size();
	int colSrc = val[0].size();

	// kiem tra ma tran vuong
	if (rowSrc != colSrc) {
		throw ("Khong the tinh dinh thuc vi ma tran khong vuong");
	}

	// kiem tra ma tran co ton tai ma tran nghich dao khong
	if ((this->determinant() == 0)) {
		throw ("Ma tran khong co ma tran nghich dao");
	}

	// i, j, k la cac bien dem, n la bien giu chieu dai canh cua ma tran vuong
	int n = rowSrc;
	double sum = 0;

	// thuat toan LUDEcomposition
	LUDecomposition(val, L, U);

	// su dung back subsitution de tim nghich dao cua ma tran L va U
	// back subsitution la phep the tung phuong trinh de giai ma tran tam giac
	vector<double> temp(n, 0);
	vector<vector<double>> backSubL(n, temp);
	vector<vector<double>> backSubU(n, temp);
	vector<vector<double>> unitMatrix(n, temp);

	for (int i = 0; i < n; i++) {
		unitMatrix[i][i] = 1;
	}

	// bien j de chay tung cot cua ma tran nghich dao can tim cho ma tran L
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			sum = 0;

			for (int k = 0; k < i; k++) {
				sum += L[i][k] * backSubL[k][j];
			}

			backSubL[i][j] = (unitMatrix[i][j] - sum) / L[i][i];
		}
	}

	// bien j de chay tung cot cua ma tran nghich dao can tim cho  ma tran U
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

const Matrix Matrix::multiply(const Matrix& other) {
	int rowSrc = (this->val).size();
	int colSrc = (this->val)[0].size();
	int rowOther = (other.val).size();
	int colOther = (other.val)[0].size();

	// khoi tao mang hai chieu bang vector, voi kich co row = rowSrc, col = colOther
	vector<double> temp(colOther, 0);
	vector<vector<double>> result(rowSrc, temp);

	// kiem tra dieu kien thuc hien duoc phep nhan hai ma tran
	if (colSrc != rowOther) {
		throw ("Khong the thuc hien phep nhan hai ma tran");
	}

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

int Matrix::rank() {
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
			if (result[i][j] != 0) {
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

const Matrix Matrix::solve(vector<vector<double>> augmentValue) {
	Matrix coeffMatrix(*this);
	Matrix result;
	Matrix rightHandMatrix(augmentValue);

	vector<vector<double>> temp(val);

	for (int i = 0; i < augmentValue.size(); i++) {
		temp[i].push_back(augmentValue[i][0]);
	}

	Matrix augmentMatrix(temp);
	int coeffMatrixRank = coeffMatrix.rank();
	int augmentMatrixRank = augmentMatrix.rank();

	if (coeffMatrixRank < augmentMatrixRank) {
		throw "He phuong trinh da cho vo nghiem";
	}
	else if (coeffMatrixRank > augmentMatrixRank) {
		throw "He phuong trinh da cho co vo so nghiem";
	}
	else {
		result = coeffMatrix.inverse();
		result = result.multiply(rightHandMatrix);
	}

	return result;
}

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

		// o vong lap nay thi bien i la dong cua L
		// bien j la cot cua U
		// vong lap nay de tinh cac thanh phan cua L
		for (i = 0; i < n; i++) {
			sum = 0;

			// tim tich cua hang i cua L va cot j cua U
			for (k = 0; k < j; k++) {
				sum = sum + L[i][k] * U[k][j];
			}
			L[i][j] = A[i][j] - sum;
		}

		// o vong lap nay thi bien j la dong cua L
		// bien i la cot cua U
		// vong lap nay de tinh cac thanh phan cua U
		for (i = 0; i < n; i++) {
			sum = 0;
			for (k = 0; k < j; k++) {
				sum = sum + L[j][k] * U[k][i];
			}
			if (L[j][j] == 0) {
				throw "error in crout algorithm";
			}
			U[j][i] = (A[j][i] - sum) / L[j][j];
		}
	}
}

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