#include <cstdlib>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <numeric>
#include <ctime>
#include <cmath>
#include <fstream> 
#include "utils.h"
#include "tvec.h"

using namespace std;

void print2DVector(vector<vector<int>> A){
	for(int i = 0;i<A.size();i++){
		for(int j=0;j<A[0].size();j++){
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
}

vector<vector<int>> initNxMVector(int n,int m){
	vector<vector<int>> res;
	for(int i=0;i<n;i++){
		vector<int> tmp;
		for(int j=0;j<m;j++){
			tmp.push_back(0);
		}
		res.push_back(tmp);
	}
	return res;
}

vector<vector<int>> initIdentetyVectorMxM(int m){
	vector<vector<int>> res = initNxMVector(m,m);
	for(int i = 0;i<m;i++){
		res[i][i]=1;
	}
	return res;
}

vector<vector<int>> transpose(vector<vector<int>> M){
	if(M.size()==0)
		return M;
	vector<vector<int>> res;
	for(int i = 0;i<M[0].size();i++){
		vector<int> tmp;
		for(int j =0;j<M.size();j++){
			tmp.push_back(M[j][i]);
		}
		res.push_back(tmp);
	}
	return res;
}

vector<vector<int>> getSubspace(vector<vector<int>> A,int rf,int rt,int cf,int ct){
	vector<vector<int>> toRet;
	for(int i =rf;i<rt;i++){
		vector<int> tmp;
		for(int j = cf;j<ct;j++){
			tmp.push_back(A[i][j]);
		}
		toRet.push_back(tmp);
	}
	return toRet;
}

vector<vector<int>> rowExchange(vector<vector<int>> M,int i,int j){
	for(int k =0;k<M[0].size();k++){
		int tmp = M[i][k];
		M[i][k]=M[j][k];
		M[j][k]=tmp;
	}
	return M;
}

vector<vector<int>> rowMultiply(vector<vector<int>> M,int i,int q){
	for(int k =0;k<M[0].size();k++){
		M[i][k]=M[i][k]*q;
	}
	return M;
}

vector<vector<int>> rowDivide(vector<vector<int>> M,int i,int q){
	for(int k =0;k<M[0].size();k++){
		M[i][k]=M[i][k]/q;
	}
	return M;
}

vector<vector<int>> rowAdd(vector<vector<int>> M,int i,int j,int q){
	for(int k =0;k<M[0].size();k++){
		M[i][k]=M[i][k]+q*M[j][k];
	}
	return M;
}
vector<vector<int>> columnExchange(vector<vector<int>> M,int i,int j){
	for(int k =0;k<M.size();k++){
		int tmp = M[k][i];
		M[k][i]=M[k][j];
		M[k][j]=tmp;
	}
	return M;
}

vector<vector<int>> columnMultiply(vector<vector<int>> M,int j,int q){
	for(int k =0;k<M.size();k++){
		M[k][j]=M[k][j]*q;
	}
	return M;
}

vector<vector<int>> columnDivide(vector<vector<int>> M,int j,int q){
	for(int k =0;k<M.size();k++){
		M[k][j]=M[k][j]/q;
	}
	return M;
}

vector<vector<int>> columnAdd(vector<vector<int>> M,int i,int j,int q){
	for(int k =0;k<M.size();k++){
		M[k][j]=M[k][j]+q*M[k][i];
	}
	return M;
}

int findIndexOfSmallestNonZeroEntryInSubrow(vector<vector<int>> M,int r,int k){
	int index,value;
	index = k;
	value = std::abs(M[r][k]);
	for(int i = k;i<M[r].size();i++){
		if((M[r][i]!=0)&&((value == 0) || (value>std::abs(M[r][i])))){
			index=i;
			value=std::abs(M[r][i]);
		}
	}
	return index;
}

int findIndexOfSmallestNonZeroentryInSubcolumn(vector<vector<int>> M,int c,int k){
	int index,value;
	index = k;
	value = std::abs(M[k][c]);
	for(int  i =k;i<M.size();i++){
		if((M[i][c]!=0)&&((value == 0) || (value>std::abs(M[i][c])))){
			index=i;
			value=std::abs(M[i][c]);
		}
	}
	return index;
}
vector<int> findIndexesOfSmallestNonZeroEntryInSubspace(vector<vector<int>> M,int k){
	int indexi,indexj,value;
	indexi = k;
	indexj = k;
	value = std::abs(M[k][k]);
	for(int i =k;i<M.size();i++){
		for(int j =k;j<M[0].size();j++){
			if((M[i][j]!=0)&&((value == 0) || (value>std::abs(M[i][j])))){
				indexi=i;
				indexj=j;
				value=std::abs(M[i][j]);
			}
		}
	}
	vector<int> ans;
	ans.push_back(indexi);
	ans.push_back(indexj);
	return ans;
}

int findIndexOfLastNonZeroEntryInSubColumn(vector<vector<int>> A,int i){
	int low =-1;
	for(int j =0;j<A.size();j++){
		if(A[j][i]==1)
			low=j;
	}
	return low;
}

int findIndexOfFirstNonZeroEntryInSubRow(vector<vector<int>> A,int i){
	for(int j =0;j<A[0].size();j++){
		if(A[i][j]==1)
			return j;
	}
	return -1;
}

vector<int> checkForDivisibility(vector<vector<int>> B,int k){
	vector<int> ret;
	for(int i = k;i<B.size();i++){
		for(int j = k;j<B[0].size();j++){
			int q = std::floor(B[i][j]/B[k][k]);
			if(q*B[k][k]!=B[i][j]){
				ret.push_back(i);
				ret.push_back(j);
				ret.push_back(q);
				return ret;
			}
		}
	}
	return ret;
}

bool subcolumnHaveNonZeroEntry(vector<vector<int>> M,int k,int l){
	for(int i = k;i<M.size();i++){
		if (M[i][l]!=0)
			return true;
	}
	return false;
}
bool subrowHaveNonZeroEntry(vector<vector<int>> M,int k,int l){
	for(int i = l;i<M[0].size();i++){
		if (M[k][i]!=0)
			return true;
	}
	return false;
}
bool subspaceHaveNonZeroEntry(vector<vector<int>> M,int k,int l){
	for(int i =k;i<M.size();i++){
		for(int j=l;j<M[0].size();j++){
			if(M[i][j]!=0){
				return true;
			}
		}
	}
	return false;
}

vector<vector<int>> multiplicationOf2DVectors(vector<vector<int>> A,vector<vector<int>> B){
	vector<vector<int>> result;
	if(A[0].size()==B.size()){
		for(int i=0;i<A.size();i++){
			vector<int> tmp;
			for(int j=0;j<B[0].size();j++){
				int c=0;
				for(int k =0;k<B.size();k++){
					c+=A[i][k]*B[k][j];
				}
				tmp.push_back(c%2);
			}	
			result.push_back(tmp);
		}
	}else{
		cout<<"Mult error"<<A.size()<<" "<<A[0].size()<<" "<<B.size()<<" "<<B[0].size()<<endl;
		exit(0);
	}
	return result;
}

vector<int> multiplicationOf2dVectorBy1DVector(vector<vector<int>> A,vector<int> b){
	vector<int> res;
	for(int i =0;i<b.size();i++){
		int c=0;
		for(int j=0;j<A.size();j++){
			c+=A[j][i]*b[i];
		}
		res.push_back(c%2);
	}
	return res;
}



vector<vector<int>> getFacesOfSimplex(vector<int> lst){
	vector<vector<int>> ret;
	for(int i =0; i<lst.size();i++){
		vector<int> tmp;
		for(int k = 0;k<lst.size();k++){
			if(k!=i)
				tmp.push_back(lst[k]);
		}
		ret.push_back(tmp);
	}
	return ret;
}
int getCoefOfSimplex(vector<vector<int>> faces,vector<int> simplex){
	if (faces[0].size()!=simplex.size())
		return 0;
	for(int i =0;i<faces.size();i++){
		int k=-1;
		for(int j =0;j<faces.size();j++){
			bool eq=true;
			for(int w=0;w<simplex.size();w++){
				if(simplex[w]!=faces[j][w]){
					eq=false;
					break;
				}
			}
			if(eq){
				k=j;
				break;
			}
		}
		if(k!=-1){
			if(k%2==0){
				return 1;
			}else{
				return -1;
			}
		}		
	}
	return 0;
}
int getCoefOfSimplexZ2(vector<vector<int>> faces,vector<int> simplex){
	if (faces[0].size()!=simplex.size())
		return 0;
	for(int i =0;i<faces.size();i++){
		int k=-1;
		for(int j =0;j<faces.size();j++){
			bool eq=true;
			for(int w=0;w<simplex.size();w++){
				if(simplex[w]!=faces[j][w]){
					eq=false;
					break;
				}
			}
			if(eq){
				k=j;
				break;
			}
		}
		if(k!=-1){
			return 1;
		}		
	}
	return 0;
}

int numberOfPivotRows(vector<vector<int>> A){
	int n = 0;
	for(int i = 0;i<A.size();i++){
		for(int j =0;j<A[0].size();j++){
			if(A[i][j]!=0){
				n++;
				break;
			}
		}
	}
	return n;
}

int numberOfPivotCols(vector<vector<int>> A){
	int n = 0;
	for(int i = 0;i<A[0].size();i++){
		for(int j =0;j<A.size();j++){
			if(A[j][i]!=0){
				n++;
				break;
			}
		}
	}
	return n;
}

//Dijikstra
float minDistance(vector<float> dist, vector<bool> sptSet){
	float min = DBL_MAX, min_index;
	for (int v = 0; v < dist.size(); v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;
}
vector<float> dijikstra(vector<vector<float>> eqDist,int i){
	vector<float> dist;
	vector<bool> sptSet;
	for(int i = 0;i<eqDist.size();i++){
		dist.push_back(DBL_MAX);
		sptSet.push_back(false);
	}
	dist[i]=0.0;
	for(int count = 0;count < eqDist.size()-1;count++){
		float u = minDistance(dist,sptSet);
		sptSet[u]=true;
		for(int v=0;v<eqDist.size();v++){
			if (!sptSet[v] && eqDist[u][v] && dist[u] != DBL_MAX && dist[u] + eqDist[u][v] < dist[v])
				dist[v] = dist[u] + eqDist[u][v];
		}
	}
	return dist;
}

vector<vector<float>> getDistacesMatrix(vector<float> x,vector<float>y){
	vector<vector<float>> eqDist;
	for (int i =0;i<x.size();i++){
		vector<float> tmp; 
		for (int j =0;j<y.size();j++){
			tmp.push_back(std::sqrt(std::pow(x[i] - x[j],2)+std::pow(y[i] - y[j],2)));
		}
		eqDist.push_back(tmp);	
	}
	vector<vector<float>> dist;
	for (int i =0;i<x.size();i++){
		dist.push_back(dijikstra(eqDist,i));
	}
	return dist;
}

int indexInVector(int i,vector<int> v){
	for(int j=0;j<v.size();j++){
		if(v[j]==i)
			return j;
	}
	return -1;
}


void storeChain(vector<vector<int>> V,vector<vector<int>> name){
	ofstream PDFile("output/H1_homology_generators.txt");
	for(int i =0;i<V[0].size();i++){
		for(int j= 0;j<V.size();j++)
			if(V[j][i]!=0)
				PDFile<< name[j][0]<<" "<< name[j][1] <<"|";
		PDFile<< endl;
	}
	PDFile.close();																																					
}

vector<vector<float>> readXYfromPSfile(char*  name){
	FILE* in;
	in = fopen(name,"r");
	vector<float> x;
	vector<float> y;
	vector<float> c;
	int n;
	int wd = fscanf(in,"%d\n",&n);
	for(int i =0;i<n;i++){
		float a,b,d;
		wd = fscanf(in,"%f %f %f\n",&a,&b,&d);
		x.push_back(a);
		y.push_back(b);
		c.push_back(d);
	}
	fclose(in);
	vector<vector<float>> res;
	res.push_back(x);
	res.push_back(y);
	res.push_back(c);
	return res;
}

void visualisePersistantDiagram(){
}

int count_spaces(string s) {
  int count = 0;

  for (int i = 0; i < s.size(); i++)
	if (s[i] == ' ') count++;

  return count;
}

float getDistance(float x1,float y1,float x2,float y2){
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

float getDistanceTVec(TVec<float>a,TVec<float>b){
	return sqrt(pow(a.getX()-b.getX(),2)+pow(a.getY()-b.getY(),2));
}

TVec<float> computeXYForce(TVec<float> c1,TVec<float> c2,float val){
	float dist=std::sqrt(std::pow((c2.getX()-c1.getX()),2)+std::pow((c2.getY()-c1.getY()),2));
	float distX = std::abs(c2.getX()-c1.getX());
	float distY = std::abs(c2.getY()-c1.getY());
	float sin=0,cos=0;
	if(dist!=0 && distX!=0)
		cos = distX/dist;
	if(dist!=0 && distY!=0)
		sin = distY/dist;
	TVec<float> ff = TVec<float>{0,0};
	if(c1.getX()>c2.getX())
		ff.setX(val*cos);
	else 
		ff.setX(val*cos*(-1));
	if(c1.getY()>c2.getY())
		ff.setY(val*sin);
	else 
		ff.setY(val*sin*(-1));
	return ff;
}

float computeForceModule(TVec<float> f){
	return sqrt(pow(f.getX(),2)+pow(f.getY(),2));
}


// Circle center 

void lineFromPoints(TVec<float> P, TVec<float> Q, float &a,float &b, float &c){
	a = Q.getY() - P.getY();
	b = P.getX() - Q.getX();
	c = a*(P.getX())+ b*(P.getY());
}
 void perpendicularBisectorFromLine(TVec<float> P, TVec<float> Q,float &a, float &b, float &c){
	TVec<float> mid_point = TVec<float>{(P.getX() + Q.getX())/2,(P.getY() + Q.getY())/2};
	// c = -bx + ay
	c = -b*(mid_point.getX()) + a*(mid_point.getY());
	float temp = a;
	a = -b;
	b = temp;
}
TVec<float> lineLineIntersection(float a1, float b1, float c1,float a2, float b2, float c2){
	float determinant = a1*b2 - a2*b1;
	if (determinant == 0){
		// The lines are parallel. This is simplified
		// by returning a pair of FLT_MAX
		return TVec<float>{FLT_MAX, FLT_MAX};
	}
 
	else
	{
		float x = (b2*c1 - b1*c2)/determinant;
		float y = (a1*c2 - a2*c1)/determinant;
		return TVec<float>{x, y};
	}
}
 
TVec<float> findCircumCenter(TVec<float> P, TVec<float> Q, TVec<float> R){
	// Line PQ is represented as ax + by = c
	float a, b, c;
	lineFromPoints(P, Q, a, b, c);
 
	// Line QR is represented as ex + fy = g
	float e, f, g;
	lineFromPoints(Q, R, e, f, g);
 
	// Converting lines PQ and QR to perpendicular
	// vbisectors. After this, L = ax + by = c
	// M = ex + fy = g
	perpendicularBisectorFromLine(P, Q, a, b, c);
	perpendicularBisectorFromLine(Q, R, e, f, g);
 
	// The point of intersection of L and M gives
	// the circumcenter
	TVec<float> circumcenter =lineLineIntersection(a, b, c, e, f, g);
 
	if (circumcenter.getX() == FLT_MAX &&
		circumcenter.getY() == FLT_MAX)
	{
		cout << "The two perpendicular bisectors "
				"found come parallel" << endl;
		cout << "Thus, the given points do not form "
				"a triangle and are collinear" << endl;
	}
	return circumcenter;
}
