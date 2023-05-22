#ifndef _alg_function_h
#define _alg_function_h

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class AlgFunction
{
public:
    AlgFunction() 
    {
    };
    virtual vector<T> SubgradientAt(vector<T> x) = 0;    
    virtual T ValueAt(vector<T> x) = 0;    
    virtual void Print() = 0;
    virtual void Inverse() = 0;
};

#endif // !_alg_function_h