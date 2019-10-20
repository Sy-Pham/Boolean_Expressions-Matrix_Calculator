#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

template <class k, class v>
class Dictionary
{
	k key;
	vector<v> value;
public:

	Dictionary();
	Dictionary(k, v);
	~Dictionary();
	Dictionary<k, v>& append(v);
	k getKey() {
		return key;
	}
	vector<v> getValue() {
		return this->value;
	}
	bool operator<(const Dictionary<k, v>& other);
};

