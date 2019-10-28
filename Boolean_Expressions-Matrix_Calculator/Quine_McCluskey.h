#pragma once
#include "QuineMcCluskyUtilitiesFunc.h"

void firstGroup(vector<int> minterms, vector<Dictionary<int, string>>& groups, int size);
vector<string> appropriateGroups(vector<Dictionary<int, string>>& groups);
vector<Dictionary<int, string>> processChart(vector<string> all);
vector<vector<string>> processCover(vector<Dictionary<int, string>> chart, vector<string> essence);
