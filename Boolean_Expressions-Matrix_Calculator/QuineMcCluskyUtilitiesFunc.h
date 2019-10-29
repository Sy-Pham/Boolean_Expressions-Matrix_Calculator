#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "Dictionary.h"
#include "Dictionary.cpp"
#include <math.h>
#include "ProcessCharacters.h"

using namespace std;


void add(vector<string>& marked, string s);
int find(vector<Dictionary<int, string>> groups, int key);
vector<string> diffence(vector<Dictionary<int, string>> tmp, vector<string> marked);
void unionArray(vector<string>& all, vector<string> unmarked);
vector<string> findEssential(vector<Dictionary<int, string>> chart);
void removeArray(vector<Dictionary<int, string>>& chart, vector<string> essence);
int findCover(vector<Dictionary<int, string>> chart, Dictionary<string, int>& res);
vector<string> findMinLen(vector<Dictionary<int, string>> chart, int idx);
vector<vector<string>> recursiveCover(vector<vector<string>> cover, int size);
vector<vector<string>> finalResult(vector<string> essence, vector<vector<string>> cover);