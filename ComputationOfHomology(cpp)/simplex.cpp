#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include "simplex.h"
#include "utils.h"
using namespace std;

Simplex::Simplex(vector<int> labels,float born,int dim){
	this->labels = labels;
	this->born = born;
	this->dim = dim;
}
Simplex::~Simplex()=default;


string Simplex::to_string(){
	string str=std::to_string(this->dim);
	str+=" [ ";
	for(int i = 0; i< this->labels.size();i++){
		str+=std::to_string(this->labels[i])+" ";
	}
	str+="]";
	str+=" "+std::to_string(this->born);
	return str;
}
