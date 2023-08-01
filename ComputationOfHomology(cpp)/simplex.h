#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "utils.h"
using namespace std;

class Simplex{
public:
	vector<int> labels;
	float born;
	int dim;
	Simplex(vector<int> labels,float born,int dim);
	~Simplex();
	string to_string();
};