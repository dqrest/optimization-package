#ifndef _alg_linear_function_h
#define _alg_linear_function_h

#include <vector>
#include <iostream>
#include "alg-function.h"

using namespace std;

template<typename T> class AlgLinearFunction : public AlgFunction <T>
{
protected:
    vector<T> c = {};
public:
    AlgLinearFunction();
    AlgLinearFunction(vector<T>);
    vector<T> SubgradientAt(vector<T> x);   
    T ValueAt(vector<T> x);
    virtual void Print();
    virtual void Inverse();
};


#endif // !_alg_function_h