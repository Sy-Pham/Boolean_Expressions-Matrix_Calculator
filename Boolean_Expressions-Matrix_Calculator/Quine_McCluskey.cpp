#include "Quine_McCluskey.h"

void firstGroup(vector<int> minterms, vector<Dictionary<int,string>> &groups, int size) {
	int minterm;
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
}

vector<string> appropriateGroups(vector<Dictionary<int, string>>& groups) {
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

		vector<string> unmarked = diffence(tmp, marked);//find elements only belond to tmp not belong to marked

		unionArray(all, unmarked);//find elements belong to unmarked not belong to all and add them into all

		if (flagStop) break;//there is one groups, nothing to do 
	}

	return all;
}

vector<Dictionary<int, string>> processChart(vector<string> all) {
	vector<Dictionary<int, string>> chart;
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

	return chart;
}

vector<vector<string>> processCover(vector<Dictionary<int, string>> chart, vector<string> essence) {
	vector<vector<string>> result;
	vector<string> cover;
	vector<vector<string>> cover1;
	//final result
	if (chart.size() == 0) {
		result.push_back(essence);//nothing to do
	}
	else {
		while (chart.size()) {
			Dictionary<string, int> cover;
			cover.~Dictionary();//destruction
			int idx = findCover(chart, cover);//find the elements are best necessary of the rest of array
			if (cover.getValue()[0] > 1) {//element appears many times
				essence.push_back(cover.getKey());//adding into essence
				vector<string> tmp;
				tmp.push_back(cover.getKey());
				removeArray(chart, tmp);//remove it from chart
			}
			else if (cover.getValue()[0] == 1) {//element appear one time
				vector<string> tmp;
				tmp = findMinLen(chart, idx);//find all the fellow elements in one group have the same special length
				cover1.push_back(tmp);
				removeArray(chart, tmp);//remove
			}
		}
		//final result
		if (cover1.size())
			result = finalResult(essence, cover1);//finding all posibilty can happen
		else
			result.push_back(essence);//ading the updated essence

	}

	return result;
}