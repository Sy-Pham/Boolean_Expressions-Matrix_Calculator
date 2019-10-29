#include "Input.h"

//Import the formula and checking
// input: string& in, int& var
// output: void
// usage: import formular include Character begining A and character '+', there is also space to seperate
void input(string& in, int& var) {//var is the maximum number of variables

	string s = "Bieu thuc nhap bi loi";
	cout << "Nhap so luong bien : ";
	cin >> var;//Import number of variables
	cout << "Nhap bieu thuc F (tu don bat dau tu A. VD: AB' + CD): ";
	cin.ignore();
	getline(cin, in);//import formula
	cout << endl;

	vector<char> a;

	for (int i = 0; i < len(in); i++) {
		if (in[i] == ' ' || in[i] == '+' || in[i] == 39)
			continue;
		//throwing error if user import the character what is out of variable range
		if (in[i] < 65 || in[i]> 65 + var - 1)
			throw s;
	}
}

// input: vector<int>& a, int x
// output: void
// usage: adding x into a
void add(vector<int>& a, int x) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == x)
			return;
	}
	// if x not belong a , x will be added
	a.push_back(x);
}

// input: an empty vector
// output: void
// usage: get the input vector
void input(vector<double>& in) {
	int dimension;

	cout << "Nhap so chieu cua vector: ";
	cin >> dimension;
	cout << "Nhap vector: ";

	for (int i = 0; i < dimension; i++) {
		double temp;
		cin >> temp;
		in.push_back(temp);
	}
}

// input: en empty 2d vector
// output: void
// usage: get the input matrix
void input(vector<vector<double>>& in) {
	int dimensionX, dimensionY;

	cout << "Nhap kich co cua ma tran:\n";
	cout << "So hang: ";
	cin >> dimensionX;
	cout << "So cot: ";
	cin >> dimensionY;
	cout << "Nhap ma tran:\n";
	vector<double> tempVector(dimensionY, 0);
	in = vector<vector<double>>(dimensionX, tempVector);

	for (int i = 0; i < dimensionX; i++) {
		for (int j = 0; j < dimensionY; j++) {
			cout << "Nhap gia tri cho phan tu [" << i << "][" << j << "]: ";
			double temp;
			cin >> temp;

			in[i][j] = temp;
		}
	}
}


