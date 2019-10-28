#pragma once
//#include "Source.h"
#include "Quine_McCluskey.h"
#include "Output.h"

int main_quine_mcCluskey() 
{
	//input
	string input;
	int var;

	try {
		input_(input, var);
	}//error 
	catch (string s) {
		cout << s;
		cout << endl << "Ket thuc chuong trinh" << endl;
		return 0;
	}

	vector<int> minterms;
	minterms = trans(input, var);//transforming input into array of interger elements
	int minterm;

	// //check input
	if (minterms.size() == 0)
	{
		cout << "\n\tF = 0\n" << endl;//nothing to do
		return 0;
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
	remove_(chart, essence);//remove these 

	//Processing cover
	vector<vector<string>> finalResult = processCover(chart, essence);

	//Out put
	output(finalResult);

	_getch();
	return 0;
}
