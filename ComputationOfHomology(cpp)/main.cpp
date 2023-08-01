#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "simplicial_complex.h"
#include "homologyGroupOfChainComplex.h"
#include "utils.h"
#include <cmath>
#include <stdlib.h>
using namespace std;
int main( int argc, char* argv[] ){
	if(argc<=3){
		cout<<" give file name, print mode, and execution mode";
		return 0;
	}
	char* fileName=argv[1];

	int printMode=atoi(argv[2]);
	int executionMode=atoi(argv[3]);
	int Dd=0;
	if(executionMode==2){
		if(argc<5){
			cout<<"Give dISTANCE AS WELL";
			return 0;
		}
				Dd=atoi(argv[4]);
	}
	vector<vector<float>> xyc=readXYfromPSfile(fileName);
	vector<vector<int>> empty;
	vector<vector<float>> distmat = getDistacesMatrix(xyc[0],xyc[1]);
	SimplicialComplex sc = SimplicialComplex(xyc[0],xyc[1],xyc[2]);
	if(printMode==1)
		sc.printSimplexes();
	sc.generateBars();
	if(executionMode>0){
		vector<vector<vector<int>>> D;
		if(executionMode!=2){
			D = sc.getBoundary(sc.selectDistance());
		}else{
			D = sc.getBoundary(Dd);
		}
		HomologyGroupOfChainComplex H = HomologyGroupOfChainComplex(D,sc.save2);
	}
	return 0;
}

