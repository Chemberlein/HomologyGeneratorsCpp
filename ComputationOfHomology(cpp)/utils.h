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
#include <float.h>
#include "tvec.h"
using namespace std;

void print2DVector(vector<vector<int>> A);
vector<vector<int>> initNxMVector(int n,int m);
vector<vector<int>> initIdentetyVectorMxM(int m);
vector<vector<int>> transpose(vector<vector<int>> M);
vector<vector<int>> getSubspace(vector<vector<int>> A,int rf,int rt,int cf,int ct);
vector<vector<int>> rowExchange(vector<vector<int>> M,int i,int j);
vector<vector<int>> rowMultiply(vector<vector<int>> M,int i,int q);
vector<vector<int>> rowDivide(vector<vector<int>> M,int i,int q);
vector<vector<int>> rowAdd(vector<vector<int>> M,int i,int j,int q);
vector<vector<int>> columnExchange(vector<vector<int>> M,int i,int j);
vector<vector<int>> columnMultiply(vector<vector<int>> M,int j,int q);
vector<vector<int>> columnDivide(vector<vector<int>> M,int j,int q);
vector<vector<int>> columnAdd(vector<vector<int>> M,int i,int j,int q);
int findIndexOfSmallestNonZeroEntryInSubrow(vector<vector<int>> M,int r,int k);
int findIndexOfSmallestNonZeroentryInSubcolumn(vector<vector<int>> M,int c,int k);
vector<int> findIndexesOfSmallestNonZeroEntryInSubspace(vector<vector<int>> M,int k);
int findIndexOfLastNonZeroEntryInSubColumn(vector<vector<int>> A,int i);
int findIndexOfFirstNonZeroEntryInSubRow(vector<vector<int>> A,int i);
vector<int> checkForDivisibility(vector<vector<int>> B,int k);
bool subcolumnHaveNonZeroEntry(vector<vector<int>> M,int k,int l);
bool subrowHaveNonZeroEntry(vector<vector<int>> M,int k,int l);
bool subspaceHaveNonZeroEntry(vector<vector<int>> M,int k,int l);
vector<vector<int>> multiplicationOf2DVectors(vector<vector<int>> A,vector<vector<int>> B);
vector<int> multiplicationOf2dVectorBy1DVector(vector<vector<int>> A,vector<int> b);
vector<vector<int>> getFacesOfSimplex(vector<int> lst);
int getCoefOfSimplex(vector<vector<int>> faces,vector<int> simplex);
int getCoefOfSimplexZ2(vector<vector<int>> faces,vector<int> simplex);
int numberOfPivotRows(vector<vector<int>> A);
int numberOfPivotCols(vector<vector<int>> A);
vector<vector<float>> getDistacesMatrix(vector<float> x,vector<float>y);
int indexInVector(int i,vector<int> v); 
void storeChain(vector<vector<int>> V,vector<vector<int>> name);
vector<vector<float>> readXYfromPSfile(char*  name);
void visualisePersistantDiagram();
void printGraph(vector<vector<float>> cordinates,vector<vector<int>> conections);
int count_spaces(string s);
float getDistance(float x1,float y1,float x2,float y2);
TVec<float> computeXYForce(TVec<float> c1,TVec<float> c2,float val);
float getDistanceTVec(TVec<float> a,TVec<float> b);
float computeForceModule(TVec<float> f);
TVec<float> findCircumCenter(TVec<float> P, TVec<float> Q, TVec<float> R);
