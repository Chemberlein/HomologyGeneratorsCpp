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
#include "homologyGroupOfChainComplex.h"
#include "utils.h"


HomologyGroupOfChainComplex::HomologyGroupOfChainComplex(vector<vector<vector<int>>> D,vector<vector<int>> names){
	SmithNormalForm KerM = SmithNormalForm(D[0]);
	KerM.computeSNF();
	this->Ker = getSubspace(KerM.Rh,0,KerM.Rh.size(),numberOfPivotCols(KerM.B),KerM.Rh[0].size());
	SmithNormalForm ImM = SmithNormalForm(D[1]);
	int imSize=0;
	if(D[1].size()!=0){
		ImM.computeSNF();
		this->Im = getSubspace(ImM.Qh,0,numberOfPivotRows(ImM.B),0,ImM.Qh[0].size());
		imSize=numberOfPivotCols(ImM.B);
	}
	quotientGroup();
	this->U = getSubspace(this->U,0,this->U.size(),imSize,this->U[0].size());
	storeChain(this->U,names);
}
HomologyGroupOfChainComplex::~HomologyGroupOfChainComplex()=default;

vector<int> HomologyGroupOfChainComplex::solve(vector<vector<int>> A,vector<int> b){
	SmithNormalForm m = SmithNormalForm(A);
	m.computeSNF();
	vector<int> c = multiplicationOf2dVectorBy1DVector(m.Qh,b);
	vector<int> u;
	for(int i =0;i<A[0].size();i++){
		if(i<c.size()){
			if(c[i]%m.B[i][i]!=0)
				cout<<"One fail"<<endl;
			u.push_back(c[i]/m.B[i][i]);
		}else{
			if(i<c.size()&&c[i]!=0)
				cout<<"Two fail"<<endl;
			u.push_back(0);
		}
	}
	return multiplicationOf2dVectorBy1DVector(m.Rh,u);
}
void HomologyGroupOfChainComplex::quotientGroup(){
	
	vector<vector<int>> A;
	if(this->Im.size()>0){
		for(int i =0;i<this->Im[0].size();i++){
			vector<int> b;
			for(int j=0;j<this->Im.size();j++){
				b.push_back(this->Im[j][i]);
			}
			vector<int> outVect =solve(this->Ker,b);
			A.push_back(outVect);
		}
		A=transpose(A);
		SmithNormalForm m = SmithNormalForm(A);
		m.computeSNF();
		this->B=m.B;
		this->U=multiplicationOf2DVectors(this->Ker,m.Q);
		this->s=m.s;
	}
	this->U=this->Ker;
	this->s=0;
}


