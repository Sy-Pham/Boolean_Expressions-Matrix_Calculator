#pragma once
#include "Source.h"

int main_quine_mcCluskey() {
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

	// Fitst grouping starts
	for (int i = 0; i < minterms.size(); i++) {
		minterm = minterms[i];
		int key = count(bin(minterm), '1');//count character '1'
		string value = zeroFill(bin(minterm), size);//fill '0' in the begining string if necessary
		//Dictionary temp(key, value);
		int index = find(groups, key);//find if key exist in array groups

		if (groups.size() == 0 || index == -1)//purely new array or failure of finding
		{
			groups.push_back(Dictionary<int, string>(key, value));//create new one
		}
		else
		{
			groups[index].append(value);//adding into value of these existing
		}
	}

	//Primary group printing starts
	sort(groups.begin(), groups.end());
	//print(groups);

	// Process for creating tables and finding appropriate groups
	vector<string> all;
	while (1) {
		vector<Dictionary<int, string>> tmp = groups;
		groups.clear();//clearing array
		int m = 0;
		bool flagStop = true;
		vector<string> marked;
		marked.clear();

		//comparing one by one elements of one groups to the next groups

		for (int i = 0; i < tmp.size() - 1; i++) {
			vector<string> v1 = tmp[i].getValue();
			for (int j = 0; j < v1.size(); j++) {
				vector<string> v2 = tmp[i + 1].getValue();
				for (int k = 0; k < v2.size(); k++) {
					int idx = -1;
					bool res = compare(v1[j], v2[k], idx);
					if (res)//if they are diffrent because of one character
					{
						int key = m;
						int index = find(groups, key);
						string value = v1[j];
						value[idx] = '-';
						if (groups.size() == 0 || index == -1)
						{
							groups.push_back(Dictionary<int, string>(key, value));//creating new one to array
						}
						else
						{
							groups[index].append(value);//adding into value those have existed
						}
						flagStop = false;

						add(marked, v1[j]);//adding normally
						add(marked, v2[k]);
					}
				}
			}
			m += 1;
		}

		vector<string> unmarked = diffence(tmp, marked);

		union_(all, unmarked);

		//print(groups);
		if (flagStop) break;//there is one groups, nothing to do 
	}

	int sz = len(minterms[minterms.size() - 1]);//length of the element in the end
	vector<Dictionary<int, string>> chart;

	//processing of chart
	for (int i = 0; i < all.size(); i++) {
		string value = all[i];
		vector<int> merge_minterms = findMinTerms(value);//array of key
		for (int j = 0; j < merge_minterms.size(); j++) {//adding these key
			int key = merge_minterms[j];

			int index = find(chart, key);

			if (chart.size() == 0 || index == -1)
			{
				chart.push_back(Dictionary<int, string>(key, value));//creating new one
			}
			else
			{
				chart[index].append(value);//adding into value these have existed
			}
		}
	}

	vector<string> essence = findEssential(chart);//finding the best necessary elements what have one of value
	remove_(chart, essence);//remove these 

	//Processing cover
	vector<vector<string>> finalResult;
	vector<string> cover;
	vector<vector<string>> cover1;
	//final result
	if (chart.size() == 0) {
		finalResult.push_back(essence);//nothing to do
	}
	else {
		while (chart.size()) {
			Dictionary<string, int> cover;
			cover.~Dictionary();//destruction
			int idx = findcover(chart, cover);//find the elements are best necessary of the rest of array
			if (cover.getValue()[0] > 1) {//element appears many times
				essence.push_back(cover.getKey());//adding into essence
				vector<string> tmp;
				tmp.push_back(cover.getKey());
				remove_(chart, tmp);//remove it from chart
			}
			else if (cover.getValue()[0] == 1) {//element appear one time
				vector<string> tmp;
				tmp = findminlen(chart, idx);//find all the fellow elements in one group have the same special length
				cover1.push_back(tmp);
				remove_(chart, tmp);//remove
			}
		}
		//final result
		if (cover1.size())
			finalResult = finalresult(essence, cover1);//finding all posibilty can happen
		else
			finalResult.push_back(essence);//ading the updated essence

	}

	//Out put
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

	_getch();
	return 0;
}

