#include "Output.h"

void output(vector<vector<string>> finalResult) {
	for (int i = 0; i < finalResult.size(); i++)
	{
		int d = finalResult[i].size();
		cout << "F = ";
		for (int j = 0; j < d; j++) {
			cout << variable(finalResult[i][j]);//transforming into formula
			if (j < d - 1) cout << " + ";
		}
		cout << endl;
	}

	cout << endl << "Ket thuc chuong trinh" << endl;
}
