#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include "Input.h"

using namespace std;

string bin(int x);
int len(string s);
int str(string a);
int count(string x, char c);
string zeroFill(string s, int size);
int len(int x);
int minlen(string s);
string variable(string s);
bool compare(string a, string b, int& index);
int len(int x);
int minlen(string s);
string variable(string s);
vector<int> dec_(string s, int var);
vector<int> trans(string s, int var);
vector<int> findMinTerms(string a);
int findchar(string x, char c);