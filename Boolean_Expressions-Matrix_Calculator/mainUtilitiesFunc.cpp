#include "MathVector.h"
#include "Matrix.h"
#include "Input.h"
#include "mainUtilitiesFunc.h"
#include "Quine_McCluskey.h"
#include "Output.h"
#include <Windows.h>

extern bool exitFlag = false;
extern bool breakSwitchFlag = false;

void mainOption() {
	cout << "Chon mot chuc nang\n" << endl;
	cout << "1 - Tim cong thuc toi tieu cua bieu thuc dai so Bool\n" << endl;
	cout << "2 - Cong hai vector\n" << endl;
	cout << "3 - Nhan vector voi mot so\n" << endl;
	cout << "4 - Tim dinh thuc cua ma tran\n" << endl;
	cout << "5 - Nghich dao cua ma tran\n" << endl;
	cout << "6 - Tich hai ma tran\n" << endl;
	cout << "7 - Tim hang cua ma tran\n" << endl;
	cout << "8 - Giai he phuong trinh tuyen tinh\n" << endl;
	cout << "9 - Thoat chuong trinh\n" << endl;
	cout << "--------------------------------------------------------\n";
	cout << "Chuc nang ban chon la: ";

	while (!exitFlag) {
		if (_kbhit()) {
			int option = _getch() - '0';

			switch (option) {
			case 1:
				mainQuineMcCluskey();
				break;
			case 2:
				mainMathVector(option);
				break;
			case 3:
				mainMathVector(option);
				break;
			case 4:
				mainMatrix(option);
				break;
			case 5:
				mainMatrix(option);
				break;
			case 6:
				mainMatrix(option);
				break;
			case 7:
				mainMatrix(option);
				break;
			case 8:
				mainMatrix(option);
			case 9:
				exitFlag = true;
				break;
			}
		}
		
	}
}

void mainReturnOrExit() {
	cout << "\n------------------------------------------------------------------\n";
	cout << "Chon chuc nang\n" << endl;
	cout << "0 - Quay lai menu chinh\n" << endl;
	cout << "9 - Thoat chuong trinh\n" << endl;

	while (!breakSwitchFlag) {
		if (_kbhit()) {
			int newOption = _getch() - '0';

			switch (newOption) {
			case 0:
				system("cls");
				mainOption();
				breakSwitchFlag = true;
				break;
			case 9:
				exitFlag = true;
				return;
			}
		}
	}
}

void mainMathVector(int option) {
	system("cls");
	switch (option) {
	case 2: {
		vector<double> in1;
		vector<double> in2;
		cout << "Nhap hai vector can cong" << endl;
		input(in1);
		input(in2);
		MathVector a(in1);
		MathVector b(in2);
		MathVector c = a.add(b);

		cout << "Ket qua phep cong hai vector la: ";
		c.output();
		break;
	}
	case 3: {
		vector<double> in;
		double scalar;
		cout << "Nhap vector va so can nhan:\n";
		input(in);
		cout << "Nhap so: ";
		cin >> scalar;
		MathVector a(in);
		MathVector b = a.multiply(scalar);

		cout << "Ket qua cua phep nhan vector voi 1 so la: ";
		b.output();
		break;
	}
	}

	mainReturnOrExit();
}

void mainMatrix(int option) {
	system("cls");

	switch (option) {
	case 4: {
		vector<vector<double>> tempMatrix;

		cout << "Nhap ma tran can tim dinh thuc:\n";
		input(tempMatrix);
		Matrix result(tempMatrix);

		try {
			int res = result.determinant();
			cout << "Dinh thuc cua ma tran la: " << res;
		}
		catch (string e) {
			cout << "Loi: " << e << endl;
		}
		break;
	}
	case 5: {
		vector<vector<double>> tempMatrix;

		cout << "Nhap ma tran can nghich dao:\n";
		input(tempMatrix);
		Matrix result(tempMatrix);

		try {
			Matrix res = result.inverse();
			cout << "Nghich dao cua ma tran tren la:\n";
			res.output();
		}
		catch (string e) {
			cout << "Loi: " << e << endl;
		}
		break;
	}
	case 6: {
		vector<vector<double>> tempMatrix1;
		vector<vector<double>> tempMatrix2;

		cout << "Nhap hai ma tran can nhan voi nhau:\n";
		cout << "Nhap ma tran 1:\n";
		input(tempMatrix1);
		cout << "Nhap ma tran 2:\n";
		input(tempMatrix2);
		Matrix a(tempMatrix1);
		Matrix b(tempMatrix2);

		try {
			Matrix result = a.multiply(b);
			cout << "Ket qua phep nhan hai ma tran tren la:\n";
			result.output();
		}
		catch (string e) {
			cout << "Loi: " << e << endl;
		}
		break;
	}
	case 7: {
		vector<vector<double>> tempMatrix;

		cout << "Nhap ma tran can tim hang:\n";
		input(tempMatrix);
		Matrix a(tempMatrix);

		int result = a.rank();
		cout << "Hang cua ma tran la: " << result;
		break;
	}
	case 8: {
		vector<vector<double>> tempMatrix;
		vector<vector<double>> tempMatrix2;

		cout << "Nhap ma tran he so:\n";
		input(tempMatrix);
		cout << "Nhap ma tran gia tri cua he phuong trinh\n";
		input(tempMatrix2);
		
		Matrix a(tempMatrix);

		try {
			Matrix result = a.solve(tempMatrix2);

			cout << "Ket qua cua he phuong trinh da cho la:\n";
			result.output();
		}
		catch (string e) {
			cout << "Loi: " << e << endl;
		}
		break;
	}
	}

	mainReturnOrExit();
}

void mainQuineMcCluskey()
{
	system("cls");
	//input
	string formula;
	int var;

	try {
		input(formula, var);
	}//error 
	catch (string s) {
		cout << s;
		cout << endl << "Ket thuc chuong trinh" << endl;
	}

	vector<int> minterms;
	minterms = trans(formula, var);//transforming input into array of interger elements
	int minterm;

	// //check input
	if (minterms.size() == 0)
	{
		cout << "\n\tF = 0\n" << endl;//nothing to do
	}
	//sort minterms
	sort(minterms.begin(), minterms.end());

	//transform chracters into numbers
	/*cout << endl;
	for (int i = 0; i < minterms.size(); i++)
		cout << minterms[i] << " ";
	cout << endl;*/

	int size = len(bin(minterms[minterms.size() - 1]));//the length of element in the end of array minterms what has transfomred into string
	vector<Dictionary<int, string>> groups;

	// First groups
	firstGroup(minterms, groups, size);

	// Process for creating tables and finding appropriate groups
	vector<string> all = appropriateGroups(groups);

	//processing of chart
	vector<Dictionary<int, string>> chart = processChart(all);

	vector<string> essence = findEssential(chart);//finding the best necessary elements what have one of value
	removeArray(chart, essence);//remove these 

	//Processing cover
	vector<vector<string>> finalResult = processCover(chart, essence);

	//Out put
	output(finalResult);

	mainReturnOrExit();
}