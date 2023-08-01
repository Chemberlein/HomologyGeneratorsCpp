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
#include "simplex.h"

using namespace std;

class SimplicialComplex {
protected:
public:
	vector<float> x;
	vector<float> y;
	vector<float> c;
	vector<int> labels;
	int nbOfPoints;
	vector<Simplex> simplexes;
	vector<Simplex> simplexesOfBoundary;
	vector<vector<int>> boundaryMatrixOfTree;
	vector<float> intS;
	vector<float> intE;
	vector<string> intN;
	vector<int> intD;
	vector<vector<int>> save2;
	SimplicialComplex(vector<float> x,vector<float> y,vector<float> c);
	virtual ~SimplicialComplex();
	void pointSpacePrint();
	void printSimplexes();
	void initBoundaryMatrixOfTree();
	void reduceBoundaryMatrix();
	void storePersistantDiagramData();
	vector<vector<vector<int>>> getBoundary(float dist);
	void generateBars();
	float selectDistance();
	std::vector<std::vector<int>> getPersistantDiagramCyclesCont();
private:	
};
