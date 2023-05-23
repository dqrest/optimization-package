// OptimizationPackage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include "optimization.h"
#include "alg-linear-function.cpp"
#include "alg-constraint.cpp"
#include "alg-simple-quadratic-function.cpp"
#include "optimization-solver.cpp"

typedef  long double ldouble;
//const ldouble UPPER_BOX = pow(10, 5), LOWER_BOX = -(10, 5);
const ldouble UPPER_BOX = 3, LOWER_BOX = -3;

using namespace std;
using namespace alglib;

int main()
{
	

	vector<ldouble> v = { -1, -1 };
	AlgLinearFunction<ldouble>* objectiveFunction = new AlgLinearFunction<ldouble>(v);
	objectiveFunction->Print();
	cout << "\n";

	vector<ldouble> upperBox = { UPPER_BOX, UPPER_BOX };
	vector<ldouble> lowerBox = { LOWER_BOX, LOWER_BOX };
	vector<ldouble> k1 = { 1, 1 };
	vector<ldouble> a1 = { 1, 1 };
	vector<ldouble> b1 = { 1, 0 };	
	AlgConstraint<ldouble> g1(new AlgSimpleQuadraticFunction<ldouble>(k1, a1, b1), 4);
	vector<AlgConstraint<ldouble>*> constraints = { &g1 };

	OptimizationSolver<ldouble>* cpSolver = new CuttingPlaneMethodWithFeasibleSetApproximationSolver<ldouble>(2, 0.0001);
	cpSolver->SetObjectiveFunction(objectiveFunction);
	cpSolver->SetLowerBox(lowerBox);
	cpSolver->SetUpperBox(upperBox);

	cpSolver->Minimize();

	delete cpSolver;
	return 0;
}
