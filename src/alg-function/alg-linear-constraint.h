#ifndef _alg_linear_constraint_h
#define _alg_linear_constraint_h

#include <vector>
#include <iostream>
#include "alg-linear-function.h"

using namespace std;

template<typename T> class AlgLinearConstraint : public AlgLinearFunction <T>
{
protected:
    T b;
public:
    AlgLinearConstraint();
    AlgLinearConstraint(vector<T> v, T b);
    void Print();
    void Inverse();    
};


#endif // !_alg_function_h