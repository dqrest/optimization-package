#ifndef _alg_simple_quadratic_function_h
#define _alg_simple_quadratic_function_h

#include <vector>
#include <iostream>
#include "alg-function.h"

using namespace std;

template<typename T> 
class AlgSimpleQuadraticFunction : public AlgFunction<T> 
{
protected:
	// Sum k_i * (a_i * x_i + b_i)^2
	vector<T> k = {};
	vector<T> a = {};
	vector<T> b = {};
public:    
	AlgSimpleQuadraticFunction(vector<T> k, vector<T> a, vector<T> b);
	virtual vector<T> SubgradientAt(vector<T> x);
	virtual T ValueAt(vector<T> x);
	virtual void Print();
	virtual void Inverse();
};


#endif // !_alg_simple_quadratic_function_h