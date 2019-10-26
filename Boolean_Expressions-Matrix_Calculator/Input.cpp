#include "Input.h"

//Import the formula and checking
void input_(string& in, int& var) {//var is the maximum number of variables

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

// adding x into a
void add_(vector<int>& a, int x) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == x)
			return;
	}
	// if x not belong a , x will be added
	a.push_back(x);
}


