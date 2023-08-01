#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "smithNormalForm.h"
#include "utils.h"
using namespace std;
class HomologyGroupOfChainComplex{
protected:
public:
	vector<vector<int>> Ker;
	vector<vector<int>> Im;
	vector<vector<int>> U;
	vector<vector<int>> B;
	int s;
	HomologyGroupOfChainComplex(vector<vector<vector<int>>> D,vector<vector<int>> names);
	virtual ~HomologyGroupOfChainComplex();
	vector<int> solve(vector<vector<int>> A,vector<int> b);
	void quotientGroup();
private:
};