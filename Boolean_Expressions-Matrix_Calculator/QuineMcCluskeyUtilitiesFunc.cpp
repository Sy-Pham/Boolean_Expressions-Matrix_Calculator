#include "QuineMcCluskyUtilitiesFunc.h"


//Finding the position where element of dictionay has the determined key 
int find(vector<Dictionary<int, string>> groups, int key) {
	for (int i = 0; i < groups.size(); i++)
	{
		int j = groups[i].getKey();//get value of key from elements of array
		if (j == key) return i;//compare
	}
	//Finding nothing
	return -1;
}

//importing string s into array of string marked
void add(vector<string> &marked, string s) {
	
	//find whether s has remained in marked
	for (int i = 0; i < marked.size(); i++) {
		if (marked[i] == s) {
			//if s has existed, do nothing
			return;
		}
	}
	//if s does not belong marked, addition will be implement
	marked.push_back(s);
	return;
}
//Export all elements of array out the screen
void print(vector<Dictionary<int, string>> groups) {
	for (int i = 0; i < groups.size(); i++) {
		cout << groups[i].getKey() << "\t\t";//key
		vector<string> value = groups[i].getValue();
		for (int i = 0; i < value.size(); i++)
			cout << value[i] << " ";//elements of value
		cout << endl;	
	}
	cout << endl;
}

//Producting the array what has the elements belonging marked and not contained in tmp
vector<string> diffence(vector<Dictionary<int, string>> tmp, vector<string> marked) {
	vector<string> res;//array result
	for (int i = 0; i < tmp.size(); i++)
	{
		vector<string> v = tmp[i].getValue();
		for (int j = 0; j < v.size(); j++) {
			int count = 0;
			for (int k = 0; k < marked.size(); k++) {
 				if (v[j] == marked[k]) count++;
				if (count) break;//element have been existing
		}
			//if array tmp does not contain those element belonged to marked, it will added into array result
			if (!count) res.push_back(v[j]);
		}
	}

	return res;
}

// Creating array has all of element both array : all and unmarked
// The elements belonging to both apprear one time
void union_(vector<string> &all,vector<string> unmarked) {

	if (all.size() == 0) {
		all = unmarked;
		return;
	}
	vector<string> res;//result

	//all of elements of all will added
	for (int i = 0; i < all.size(); i++)
		res.push_back(all[i]);
	//only the elements of unmarked not contained in all will added
	for (int i = 0; i < unmarked.size(); i++) {
		int count = 0;
		for (int j = 0; j < all.size(); j++) {
			if (all[j] == unmarked[i]) count++;
			if (count) break;//do nothing because it have added before
		}
		if (!count) all.push_back(unmarked[i]);//adding
	}

}

//Creating the array of string from elements of chart which its value has one 
// no element is repeated
vector<string> findEssential(vector<Dictionary<int, string>> chart) {
	vector<string> res;
	for (int i = 0; i < chart.size(); i++) {
		if (chart[i].getValue().size() == 1)//the elements has value what has only one element
		{
			string v = chart[i].getValue()[0];
			int count = 0;
			for (int j = 0; j < res.size(); j++) {
				if (res[j] == v) 
					count++;
				if (count) break;//do nothing because it have added before
			}
			//if the string haven't existed, it will added
			if (count == 0) res.push_back(v);
		}
	}

	return res;
}

//all elements has key what is the same as transformed from essence will be eleminate from array chart
void remove_(vector<Dictionary<int, string>>&chart, vector<string> essence) {
	for (int i = 0; i < essence.size(); i++) {
		vector<int > k = findMinTerms(essence[i]);//transforming string into int
		for (int j = 0; j < k.size(); j++) {
			int key = k[j];
			int idx = find(chart, key);//finding
			if(idx!=-1)//if finding successfully, it is removed
				chart.erase(chart.begin() + idx);
		}	
	}
}
 
//finding the string that has the appearance is the best popular in chart
//value of res is the number of appearance of key
int findcover(vector<Dictionary<int, string>> chart, Dictionary<string,int> &res) {
	int d = chart.size();
	string s = chart[0].getValue()[0];
	int max = 1;// the number of appearance
	int idx = 0;//index
	int count=1;
	//Selection Algorithm
	for (int i = 0; i < d - 1; i++) {
		vector<string> v1 = chart[i].getValue();
		for (int i1 = 0; i1 < v1.size(); i1++) {
			count = 1;
			string val1 = v1[i1];
			//coparing with rest continuting of elements of chart
			for (int j = i + 1; j < d; j++) {
				vector<string> v2 = chart[j].getValue();
				for (int j1 = 0; j1 < v2.size(); j1++) {
					string val2 = v2[j1];
					if (val1 == val2) count++;
				}
			}

			if (count > max) {
				max = count;
				s = val1;
				idx = i;
			}
		}
	}
	
	Dictionary<string, int> tmp(s, max);
	res = tmp;

	return idx;
}

//Finding string has shortest special length from elements of value 
//idx is index of the element in chart
vector<string> findminlen(vector<Dictionary<int, string>> chart, int idx){
	vector<string> res;
	vector<string> value = chart[idx].getValue();
	int min = minlen(value[0]);//minlen() is function to identify the special length
	int d = value.size();
	for (int i = 1; i < d; i++)
	{
		if (minlen(value[i]) < min)
			min = minlen(value[i]);
	}
	for (int i = 0; i < d; i++)
	{
		//if there are some elements has the same special length , all of them will added
		if (minlen(value[i]) == min)
			res.push_back(value[i]);
	}

	return res;
}

//Finding the most appropriate elements to cover all the rest of algorithm
//size is size of array cover
vector<vector<string>> recursiveCover(vector<vector<string>> cover,int size) {
	vector<vector<string>> res;
	if (size == 1)//one element
	{
		int sz = cover[size - 1].size();
		for (int i = 0; i < sz; i++)
		{
			//Taking all elements
			vector<string> tmp;
			tmp.push_back(cover[size - 1][i]);
			res.push_back(tmp);
		}
		
		return res;
	}
	
	res = recursiveCover(cover, size - 1);
	int sz = res.size();
	//the existing elements will added the new factor
	for (int i = 0; i < sz; i++) {
		vector<string> tmp;
		for (int j = 0; j < cover[size - 1].size(); j++) {
			tmp = res[i];
			tmp.push_back(cover[size - 1][j]);
			res.push_back(tmp);
		}
	}
	//remove all the old elements
	res.erase(res.begin(),res.begin() + sz);

	return res;
}

//Combining essence and cover to export the finally result
vector<vector<string>> finalresult(vector<string> essence, vector<vector<string>> cover) {
	vector<vector<string>> res;
	res = recursiveCover(cover, cover.size());//all elements of cover
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < essence.size(); j++) {
			res[i].push_back(essence[j]);//these elements will be combined all of elements of essence
		}
	
	}

	return res;
}
