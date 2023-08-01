#include <cstdlib>
#include <iostream>
#include <fstream> 
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <numeric>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "smithNormalForm.h"
#include "utils.h"
using namespace std;

SmithNormalForm::SmithNormalForm(vector<vector<int>> V){
	B = V;
}

SmithNormalForm::~SmithNormalForm()=default;


void SmithNormalForm::rowExchangeOperation(int i,int j){
	B=rowExchange(B,i,j);
	Qh=rowExchange(Qh,i,j);
	Q=columnExchange(Q,i,j);
}

void SmithNormalForm::rowMultiplyOperation(int i,int mult){
	B=rowMultiply(B,i,mult);
	Qh=rowMultiply(Qh,i,mult);
	Q=columnMultiply(Q,i,mult);
}

void SmithNormalForm::rowDivideOperation(int i,int q){
	B=rowDivide(B,i,q);
	Qh=rowDivide(Qh,i,q);
	Q=columnDivide(Q,i,q);
}

void SmithNormalForm::rowAddOperation(int i,int j,int q){
	B=rowAdd(B,i,j,q);
	Qh=rowAdd(Qh,i,j,q);
	Q=columnAdd(Q,i,j,-q);
}

void SmithNormalForm::columnExchangeOperation(int i,int j){	
	B=columnExchange(B,i,j);
	Rh=columnExchange(Rh,i,j);
	R=rowExchange(R,i,j);
	if(SimOpCR.size()!=0)
		SimOpCR=rowExchange(SimOpCR,i,j);
}

void SmithNormalForm::columnMultiplyOperation(int i,int mult){
	B=columnMultiply(B,i,mult);
	Rh=columnMultiply(Rh,i,mult);
	R=rowMultiply(R,i,mult);
	if(SimOpCR.size()!=0)
		SimOpCR=rowMultiply(SimOpCR,i,mult);
}

void SmithNormalForm::columnDivideOperation(int i,int q){
	B=columnDivide(B,i,q);
	Rh=columnDivide(Rh,i,q);
	R=rowDivide(R,i,q);
	if(SimOpCR.size()!=0)
		SimOpCR=rowDivide(SimOpCR,i,q);
}

void SmithNormalForm::columnAddOperation(int i,int j,int q){
	B=columnAdd(B,i,j,q);
	Rh=columnAdd(Rh,i,j,q);
	R=rowAdd(R,i,j,-q);
	if(SimOpCR.size()!=0)
		SimOpCR=rowAdd(SimOpCR,i,j,-q);
}
void SmithNormalForm::partRowReduce(int k,int l){
	for(int i =k+1;i<B.size();i++){
		if(B[i][l]!=0){
			int q = std::floor(B[i][l]/B[k][l]);
			rowAddOperation(i,k,-1*q);
		}
	}
}
void SmithNormalForm::partColumnReduce(int k,int l){
	for(int i =l+1;i<B[0].size();i++){
		if(B[k][i]!=0){
			int q = std::floor(B[k][i]/B[k][l]);
			columnAddOperation(l,i,-1*q);
		}
	}
}

void SmithNormalForm::moveMinNonzero(int k){
	vector<int> ij=findIndexesOfSmallestNonZeroEntryInSubspace(B,k);
	rowExchangeOperation(k,ij[0]);
	columnExchangeOperation(k,ij[1]);
}
void SmithNormalForm::partSmithForm(int k){
	vector<int> divisible;
	bool stop = false;
	do{
		moveMinNonzero(k);
		partRowReduce(k,k);
		if(subcolumnHaveNonZeroEntry(B,k+1,k)){
			continue;
		}
		partColumnReduce(k,k);
		if(subrowHaveNonZeroEntry(B,k,k+1)){
			continue;
		}
		divisible=checkForDivisibility(B,k);
		if(divisible.size()==0)
			stop=true;
		if(divisible.size()!=0){
			rowAddOperation(divisible[0],k,1);
			columnAddOperation(k,divisible[1],-1*divisible[2]);
		}
	}while(!stop);
}

void SmithNormalForm::computeSNF(){
	if(B.size()==0)
		return;
	if(Q.size()==0)
		Q=initIdentetyVectorMxM(B.size());
	if(Qh.size()==0)
		Qh=initIdentetyVectorMxM(B.size());
	if(R.size()==0)
		R=initIdentetyVectorMxM(B[0].size());
	if(Rh.size()==0)
		Rh=initIdentetyVectorMxM(B[0].size());
	int s=0;
	int t=-1;
	while(subspaceHaveNonZeroEntry(B,t+1,t+1)){
		t++;
		partSmithForm(t);
		if(B[t][t]<0){
			rowMultiplyOperation(t,-1);
		}
		if(B[t][t]==1)
			s++;
	}
	t=t;
	s=s;
}
void SmithNormalForm::setQ(vector<vector<int>> V){
	Q=V;
}
void SmithNormalForm::setQh(vector<vector<int>> V){
	Qh=V;
}
void SmithNormalForm::setR(vector<vector<int>> V){
	R=V;
}
void SmithNormalForm::setRh(vector<vector<int>> V){
	Rh=V;
}
void SmithNormalForm::setSimOpCR(vector<vector<int>> V){
	SimOpCR=V;
}