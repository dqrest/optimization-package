﻿// OptimizationPackage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include "optimization.h"
#include "alg-linear-function.cpp"
#include "alg-constraint.cpp"
#include "alg-simple-quadratic-function.cpp"
#include "optimization-solver.cpp"

typedef  long double ldouble;


using namespace std;
using namespace alglib;

int main()
{

	vector<ldouble> v = { -1, -1 };
	AlgLinearFunction<ldouble>* objectiveFunction = new AlgLinearFunction<ldouble>(v);
	objectiveFunction->Print();
	cout << "\n";

	vector<ldouble> k1 = { 1, 1 };
	vector<ldouble> a1 = { 1, 1 };
	vector<ldouble> b1 = { 1, 0 };
	AlgSimpleQuadraticFunction<ldouble> quad1(k1, a1, b1);
	AlgConstraint<ldouble> g1(&quad1, 4);
	g1.Print();

	
	OptimizationSolver<ldouble>* cpSolver = new CuttingPlaneMethodWithFeasibleSetApproximationSolver<ldouble>(2, 0.0001);
	cpSolver->SetObjectiveFunction(objectiveFunction);
	delete cpSolver;
	return 0;
}
