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
#include "simplicial_complex.h"
#include "simplex.h"
#include "utils.h"
using namespace std;

SimplicialComplex::SimplicialComplex(vector<float> x,vector<float>y,vector<float>c){
	this->x=x;
	this->y=y;
	this->c=c;
	//for(int i =0;i<this->x.size();i++){
	//	std::cout<<x[i]<<std::endl;
	//}
	this->nbOfPoints = this->x.size();
	for (int i =0;i<x.size();i++){
		this->labels.push_back(i);
	}

	for(int i = 0;i<this->nbOfPoints;i++){
		vector<int> l;
		l.push_back(i);
		this->simplexes.push_back(Simplex(l,0,0));
	}
	for(int i = 0;i<this->nbOfPoints;i++){
		for(int j = i+1;j<this->nbOfPoints;j++){
			vector<int> l;
			l.push_back(i);
			l.push_back(j);
			//std::cout<<std::sqrt(std::pow(this->x[i]-this->x[j],2)+std::pow(this->y[i]-this->y[j],2))<<std::endl;
			this->simplexes.push_back(Simplex(l,std::sqrt(std::pow(this->x[i]-this->x[j],2)+std::pow(this->y[i]-this->y[j],2)+std::pow(this->c[i]-this->c[j],2)),2));
		}
	}
	for(int i = 0;i<this->nbOfPoints;i++){
		for(int j = i+1;j<this->nbOfPoints;j++){
			for(int k = j+1;k<this->nbOfPoints;k++){
				vector<int> l;
				l.push_back(i);
				l.push_back(j);
				l.push_back(k);
				float minb3=std::sqrt(std::pow(x[i]-x[j],2)+std::pow(y[i]-y[j],2)+std::pow(c[i]-c[j],2));
				if(minb3<std::sqrt(std::pow(x[i]-x[k],2)+std::pow(y[i]-y[k],2)+std::pow(c[i]-c[k],2)))
					minb3=std::sqrt(std::pow(x[i]-x[k],2)+std::pow(y[i]-y[k],2)+std::pow(c[i]-c[k],2));
				if(minb3<std::sqrt(std::pow(x[j]-x[k],2)+std::pow(y[j]-y[k],2)+std::pow(c[j]-c[k],2)))
					minb3=std::sqrt(std::pow(x[j]-x[k],2)+std::pow(y[j]-y[k],2)+std::pow(c[j]-c[k],2));
				this->simplexes.push_back(Simplex(l,minb3,3));
			}
		}
	}

	std::sort(this->simplexes.begin(),this->simplexes.end(),[](const Simplex& lhs, const Simplex& rhs){return lhs.born < rhs.born || (lhs.born == rhs.born and lhs.dim < rhs.dim);});
}
SimplicialComplex::~SimplicialComplex()=default;

void SimplicialComplex::pointSpacePrint(){
	for(int i=0;i<this->nbOfPoints;i++){
		cout<<this->x[i]<<" "<<this->y[i]<<" "<<this->labels[i]<<endl;
	}
}

void SimplicialComplex::printSimplexes(){
	for(int i = 0;i<this->simplexes.size();i++)
		cout<< this->simplexes[i].to_string()<< endl;
}



void SimplicialComplex::initBoundaryMatrixOfTree(){
	vector<vector<int>> simplexesLabels;
	for(int  i = 0;i<this->simplexes.size();i++){
			simplexesLabels.push_back(this->simplexes[i].labels);
			simplexesOfBoundary.push_back(this->simplexes[i]);	
	}
	for(int i =0; i<simplexesLabels.size();i++){
		vector<vector<int>> faces = getFacesOfSimplex(simplexesLabels[i]);
		vector<int> tmp;
		for(int j =0; j<simplexesLabels.size();j++){
			tmp.push_back(getCoefOfSimplexZ2(faces,simplexesLabels[j]));
		}		
		this->boundaryMatrixOfTree.push_back(tmp);
	}
	this->boundaryMatrixOfTree=transpose(this->boundaryMatrixOfTree);
}



void SimplicialComplex::reduceBoundaryMatrix(){
vector<string> trackOfChains;

	for(int i =0;i<this->simplexesOfBoundary.size();i++){
		string str = "";
		for(int j =0;j<this->simplexesOfBoundary[i].labels.size();j++){
			if (j!=0)
				str+=" ";
			str+= std::to_string(this->simplexesOfBoundary[i].labels[j]);
		}
		str+="|";
		trackOfChains.push_back(str);
	}	
	vector<int> lowestEntrys;	
	for (int i =0;i<this->boundaryMatrixOfTree.size();i++){
		lowestEntrys.push_back(findIndexOfLastNonZeroEntryInSubColumn(this->boundaryMatrixOfTree,i));
	}
	for (int i =0;i<this->boundaryMatrixOfTree.size();i++){
		bool stop=false;
		while(!stop){
			stop=true;
			int lowi = lowestEntrys[i];//findIndexOfLastNonZeroEntryInSubColumn(this->boundaryMatrixOfTree,i);
			if(lowi==-1)
				break;
			for(int j =0;j<i;j++){
				int lowj=lowestEntrys[j];//findIndexOfLastNonZeroEntryInSubColumn(this->boundaryMatrixOfTree,j);
				if(lowi==lowj){
					for(int k =0;k<this->boundaryMatrixOfTree.size();k++){
						this->boundaryMatrixOfTree[k][i] = (this->boundaryMatrixOfTree[k][i]+this->boundaryMatrixOfTree[k][j])%2; 
					}
					lowestEntrys[i]=findIndexOfLastNonZeroEntryInSubColumn(this->boundaryMatrixOfTree,i);
					trackOfChains[i]+=trackOfChains[j];
					stop=false;
					break;
				}
			}
		} 
	}
	for (int i =0;i<this->boundaryMatrixOfTree.size();i++){
		if(lowestEntrys[i]!=-1)
			continue;
		float start =this->simplexesOfBoundary[i].born;
		int dim = this->simplexesOfBoundary[i].dim;
		float end =-1;
		for(int j=0;j<this->boundaryMatrixOfTree.size();j++){
			if(this->boundaryMatrixOfTree[i][j]==1){
				bool nashli_eshe_edinicu = false;
				if(i==lowestEntrys[j]){
					end = this->simplexesOfBoundary[j].born;
					break;
				}
			}
		}
		this->intS.push_back(start);
		this->intE.push_back(end);
		this->intD.push_back(dim);
		this->intN.push_back(trackOfChains[i]);
	}
}

void SimplicialComplex::storePersistantDiagramData(){
	ofstream PDFile("output/Persistant_Diagram_Data.txt");
	for(int i =0;i<this->intN.size();i++)
			if(this->intS[i]<this->intE[i] )
				PDFile<< this->intN[i]  << this->intS[i]<<" "<<this->intE[i]<< endl;
	PDFile.close();
}

vector<vector<vector<int>>> SimplicialComplex::getBoundary(float dist){
	vector<vector<int>> simplexes_size_one;
	vector<vector<int>> simplexes_size_two;
	vector<vector<int>> simplexes_size_three;
	for(int  i = 0;i<this->simplexes.size();i++){
		if(simplexes[i].born<dist || dist==-1){
			if(this->simplexes[i].labels.size()==1){
				simplexes_size_one.push_back(this->simplexes[i].labels);
			}else if(this->simplexes[i].labels.size()==2){
				simplexes_size_two.push_back(this->simplexes[i].labels);
			}else if(this->simplexes[i].labels.size()==3){
				simplexes_size_three.push_back(this->simplexes[i].labels);
			}
		}
	}
	std::sort(simplexes_size_one.begin(),simplexes_size_one.end(),[](const vector<int>& lhs, const vector<int>& rhs){return lhs[0]< rhs[0];});
	std::sort(simplexes_size_two.begin(),simplexes_size_two.end(),[](const vector<int>& lhs, const vector<int>& rhs){return lhs[0]< rhs[0] || (lhs[0]==rhs[0]&&lhs[1]< rhs[1]);});
	std::sort(simplexes_size_three.begin(),simplexes_size_three.end(),[](const vector<int>& lhs, const vector<int>& rhs){return lhs[0]< rhs[0] || (lhs[0]==rhs[0]&&lhs[1]< rhs[1])|| (lhs[0]==rhs[0]&&lhs[1]==rhs[1]&&lhs[2]< rhs[2]);});
	vector<vector<int>> D0;
	for(int i =0;i<simplexes_size_two.size();i++){
		vector<vector<int>> faces = getFacesOfSimplex(simplexes_size_two[i]);
		vector<int> tmp;
		for(int j =0;j<simplexes_size_one.size();j++){
			tmp.push_back(getCoefOfSimplex(faces,simplexes_size_one[j]));
		}
		D0.push_back(tmp);
	}
	D0=transpose(D0);
	vector<vector<int>> D1;
	for(int i =0;i<simplexes_size_three.size();i++){
		vector<vector<int>> faces = getFacesOfSimplex(simplexes_size_three[i]);
		vector<int> tmp;
		for(int j =0;j<simplexes_size_two.size();j++){
			tmp.push_back(getCoefOfSimplex(faces,simplexes_size_two[j]));
		}
		D1.push_back(tmp);
	}
	D1=transpose(D1);
	vector<vector<vector<int>>> ret;
	ret.push_back(D0);
	ret.push_back(D1);
	this->save2=simplexes_size_two;
	return ret;
}
void SimplicialComplex::generateBars(){
	initBoundaryMatrixOfTree();
	reduceBoundaryMatrix();
	storePersistantDiagramData();
}
std::vector<std::vector<int>> SimplicialComplex::getPersistantDiagramCyclesCont(){
	std::vector<std::vector<int>> res;
	std::vector<int> verteces;
	for(int i = 0;i<intS.size();i++){
		if(intE[i]==-1 || intE[i]-intS[i]>0){
			verteces.clear();
			std::string s = intN[i];
			std::string delimiter = "|";
			std::string delimiter2 = " ";
			size_t pos = 0;
			std::string token;
			bool dim2=true;
			while ((pos = s.find(delimiter)) != std::string::npos) {
		    	token = s.substr(0, pos);
		    	if(count_spaces(token)!=1){
		    		dim2=false;
		    		break;
		    	}
		    	size_t spos=token.find(delimiter2);
		    	if(std::find(verteces.begin(),verteces.end(),std::stoi(token.substr(0,spos)))==verteces.end())
		    		verteces.push_back(std::stoi(token.substr(0,spos)));
		    	token.erase(0, spos + delimiter2.length());
		    	if(std::find(verteces.begin(),verteces.end(),std::stoi(token))==verteces.end())
		    		verteces.push_back(std::stoi(token));
		    	s.erase(0, pos + delimiter.length());
			}
			if(dim2){
				res.push_back(verteces);
			}
		}
	}
	return res;
}
float SimplicialComplex::selectDistance(){
	float maxL = 0;
	float dist = 1;
	// don't forget dimention 
	for(int i =0;i<this->intN.size();i++){
		if(this->intD[i]==2){
			if(this->intE[i]==-1)
				return -1;
			if(maxL <this->intE[i]-this->intS[i]){
				maxL=this->intE[i]-this->intS[i];
				dist= this->intS[i]+(this->intE[i]-this->intS[i])/2;
			}
		}
	}
	return dist;
}