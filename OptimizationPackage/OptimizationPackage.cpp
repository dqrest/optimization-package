// OptimizationPackage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include "optimization.h"
#include "alg-linear-function.cpp"
#include "alg-linear-constraint.cpp"

typedef  long double ldouble;


using namespace std;
using namespace alglib;

int main()
{
	vector<ldouble> v = { 1, 2, 3 };
	AlgLinearFunction<ldouble> c(v);
	c.Print();
	cout << "\n";
	AlgLinearConstraint<ldouble> lc(v, 1);
	lc.Inverse();
	lc.Print();

	return 0;
}
