// OptimizationPackage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "alg-function.cpp"
#include <iostream>
#include "optimization.h"


using namespace std;
using namespace alglib;

int main()
{
	vector<long double> v = { 1, 2, 3 };
	AlgLinearFunction<long double> c(v);
	c.Print();
	//c.Print();

	return 0;
}
