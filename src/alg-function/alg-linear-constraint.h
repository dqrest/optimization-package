#ifndef _alg_linear_constraint_h
#define _alg_linear_constraint_h

#include <vector>
#include <iostream>
#include "alg-linear-function.h"

using namespace std;

template<typename T> 
class AlgLinearConstraint : public AlgLinearFunction <T>
{
protected:
    T b;
public:
    AlgLinearConstraint();
    AlgLinearConstraint(vector<T> v, T b);
    void Print();
    void Inverse();    
};

template<typename T> 
class AlgBoxConstraint : public AlgLinearFunction<T>
{
private:
	int _ind = -1;
	string _lower;
	string _upper;
	int _dimension = -1;
	vector<T> c = {};
public:
	AlgBoxConstraint<T>(int dimension, int ind, vector<string> b);	
	void Print();	
	int GetInd();	
	double GetLower();	
	double GetUpper();	
};


#endif // !_alg_function_h