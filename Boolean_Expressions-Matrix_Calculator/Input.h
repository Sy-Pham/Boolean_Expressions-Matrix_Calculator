#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include "ProcessCharacters.h"
#include "QuineMcCluskyUtilitiesFunc.h"
#include "MathVector.h"
#include "Matrix.h"
using namespace std;

// input for boolean expression
void input_(string& in, int& var);
void add_(vector<int>& a, int x);

// input for math vector
void input(vector<double>& in);

// input for matrix
void input(vector<vector<double>>& in);