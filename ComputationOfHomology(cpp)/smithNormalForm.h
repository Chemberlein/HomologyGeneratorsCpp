#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <numeric>
#include <ctime>
#include <cmath>
#include "utils.h"
using namespace std;


class SmithNormalForm {
protected:
public:
	vector<vector<int>> B;
	vector<vector<int>> Q;
	vector<vector<int>> Qh;
	vector<vector<int>> R;
	vector<vector<int>> Rh;
	vector<vector<int>> SimOpCR;

	int t;
	int s;
	SmithNormalForm(vector<vector<int>> V);
	virtual ~SmithNormalForm();
	void rowExchangeOperation(int i,int j);
	void rowMultiplyOperation(int i,int mult);
	void rowDivideOperation(int i,int q);
	void rowAddOperation(int i,int j,int q);
	void columnExchangeOperation(int i,int j);
	void columnMultiplyOperation(int i,int mult);
	void columnDivideOperation(int i,int q);
	void columnAddOperation(int i,int j,int q);
	void partRowReduce(int k,int l);
	void partColumnReduce(int k,int l);
	void moveMinNonzero(int k);
	void partSmithForm(int k);
	void computeSNF();
	void setQ(vector<vector<int>> V);
	void setQh(vector<vector<int>> V);
	void setR(vector<vector<int>> V);
	void setRh(vector<vector<int>> V);
	void setSimOpCR(vector<vector<int>> V);
private:	
};