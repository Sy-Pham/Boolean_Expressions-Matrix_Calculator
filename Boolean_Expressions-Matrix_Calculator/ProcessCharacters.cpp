#define _CRT_SECURE_NO_WARNINGS
#include "ProcessCharacters.h"

//transforming the number of decimal into binary
string bin(int x) {
	char s[20];
	_itoa(x, s, 2);
	string c = s;

	return c;
}

// Evaluate the length of sequence of characters
int len(string s) {
	return s.size();
}

//transforming the sequence of characters into decimal
int str(string a) {
	int d = len(a);
	int count = 0;
	int exp = 0;//exponent
	char c;

	for (int i = d - 1; i >= 0; i--, exp++) {
		c = a[i];
		count = count + atoi(&c) * pow(2, exp);//transformed from binary
	}
	return count;
}

// Evaluating the quantity of character c contained in determined string s
int count(string x, char c) {
	int count = 0;
	for (int i = 0; i < len(x); i++)
		if (x[i] == c) count++;

	return count;
}

//Find the first position where character c belong to string s
int findchar(string x, char c) {
	for (int i = 0; i < len(x); i++) {
		if (x[i] == c) return i;
	}

	return -1;
}

//filling number zero into the begin of the string s in order to fit the length of size
string zeroFill(string s, int size) {
	int d = len(s);
	if (d >= size) return s;
	string c;
	for (int i = 0; i < size - d; i++)
		c = c + "0";
	//adding sequence of characters contain only '0'
	s = c + s;

	return s;
}
//finding the first position string a has character what not belong string b if a is different from b
// return true if a have only 1 character not belong b and ortherwise return false
bool compare(string a, string b, int& index) {
	int count = 0;
	for (int i = 0; i < len(a); i++)
	{
		if (a[i] != b[i])
		{
			// position completely found
			index = i;
			count++;
			if (count > 1)
				return false;
		}
	}
	// a and b are the same 
	return true;
}

//Evaluating the length of x 
int len(int x) {
	int count = 1;
	while (x / 10 != 0)
	{
		count++;
		x = x % 10;//take the redundant of operator diving 10
	}

	return count;
}

//transforimg string s into sequence of characters of the Alphabet
string variable(string s) {
	string res;
	char c = 65;// Character A
	for (int i = 0; i < len(s); i++, c++) {//character c is creased gradually after each loop
		//character '1' is absolute and '0' is opposite
		if (s[i] == '0') res = res + c + "'";
		else if (s[i] == '1') res = res + c;
	}

	return res;
}

//Evaluating the quantity of characters contained in s what is different from character '-'
int minlen(string s) {
	int count = 0;
	for (int i = 0; i < len(s); i++) {
		if (s[i] != '-') count++;
	}

	return count;
}

// Find all of number of decimal what are transformed from string s
vector<int> dec_(string s, int var) {//Var is the maximum quantity of variable
	char c = 65; // character A - character to estimate
	char ch = 39;// character '
	int idx = 0;
	int l = len(s);
	string str;

	while (idx < l) {
		// Absent positions of character are filled by character '-'
		if (s[idx] != c) {
			str = str + '-';
		}
		else {
			//absolute character is replaced by '1' and orthewise is '0'
			if (idx + 1 < l)
				if (s[idx + 1] == ch) {
					str = str + '0';
					idx++;
				}
				else str = str + '1';
			else
				str = str + '1';
			idx++;
		}
		c++;//increse character estimator

	}
	//filling character '-' in the end of sequence of character to obtain the lenghth as variable's number of maximum
	for (int i = len(str); i < var; i++) {
		str = str + '-';
	}

	//transforming string into the array of numbers
	vector<int> res = findMinTerms(str);
	return res;
}

//transforming string what have imported from user into the array of numbers
vector<int> trans(string s, int var) {//Var is the maximum quantity of variable
	vector<int> res;

	int l = len(s);
	int i = 0;
	while (i < l) {
		string s1 = "";
		//Taking appropriate characters
		while (s[i] != ' ' && s[i] != '+' && i < l) {
			s1 = s1 + s[i];
			if (s[i + 1] == 39) {
				s1 = s1 + s[i + 1];
				i++;
			}
			i++;
		}
		//ignoring the redundant characters
		while (s[i] == ' ' || s[i] == '+')
			i++;

		//adding into array
		vector<int> arr = dec_(s1, var);
		for (int j = 0; j < arr.size(); j++) {

			add_(res, arr[j]);
		}

	}

	return res;
}

//transforming string into the array of numbers
vector<int> findMinTerms(string a) {

	vector<int> res;
	int gaps = count(a, '-');//counting the number of character '-'
	if (gaps == 0) {
		res.push_back(str(a));//adding into array
		return res;
	}

	//exponent of 2 because there are two way to fill the position character is '-'

	vector<string> x;
	for (int i = 0; i < pow(2, gaps); i++) {
		x.push_back(zeroFill(bin(i), gaps));//Creating the array of characters including only '0' and '1' 
	}

	for (int i = 0; i < pow(2, gaps); i++) {//fill zero or one into the position character is '-'

		for (int j = 0; j < x.size(); j++) {
			string temp = a;
			int idx = -1;

			for (int k = 0; k < len(x[j]); k++) {
				//fiding the position character is '-' and replace these character by 0 or 1 sequencely from aforementioned array x
				char c = x[j][k];
				if (idx != -1) {
					idx = idx + findchar(&temp[idx + 1], '-') + 1;
				}
				else {
					idx = findchar(&temp[idx + 1], '-');
				}
				temp[idx] = c;
			}
			res.push_back(str(temp));//adding into array
		}

		return res;
	}
}