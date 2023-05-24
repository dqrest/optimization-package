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
const ldouble UPPER_BOX = 100, LOWER_BOX = -100;

using namespace std;
using namespace alglib;


vector<ldouble> initVector(size_t dim, ldouble elem)
{
	vector<ldouble> zero = {};
	for (size_t i = 0; i < dim; i++)
		zero.push_back(elem);
	return zero;
}

void test1(size_t dim)
{
	// init objective function
	vector<ldouble> c = initVector(dim, -1);
	//c[0] = -1;
	//for (size_t i = 0; i < dim; i++)
	//  c.push_back(-1);
	AlgLinearFunction<ldouble>* objectiveFunction = new AlgLinearFunction<ldouble>(c);

	// init box constraints
	vector<ldouble> upper = { };
	vector<ldouble> lower = { };
	for (size_t i = 0; i < dim; i++) {
		upper.push_back(UPPER_BOX);
		lower.push_back(LOWER_BOX);
	}

	// init simple quadratic constraints
	vector<AlgConstraint<ldouble>*> constraints = {};
	for (size_t i = 0; i < dim; i++) {
		vector<ldouble> bPlus = initVector(dim, 0);
		vector<ldouble> bMinus = initVector(dim, 0);
		bPlus[i] = 1;
		bMinus[i] = -1;
		vector<ldouble> k = initVector(dim, 1);
		vector<ldouble> a = initVector(dim, 1);

		AlgConstraint<ldouble>* g1 = new AlgConstraint<ldouble>(new AlgSimpleQuadraticFunction<ldouble>(k, a, bPlus), 4);
		AlgConstraint<ldouble>* g2 = new AlgConstraint<ldouble>(new AlgSimpleQuadraticFunction<ldouble>(k, a, bMinus), 4);
		constraints.push_back(g1);
		constraints.push_back(g2);		
	}

	OptimizationSolver<ldouble>* cpSolver = new CuttingPlaneMethodWithFeasibleSetApproximationSolver<ldouble>(dim, 0.00000001);
	cpSolver->SetObjectiveFunction(objectiveFunction);
	cpSolver->SetConstraints(constraints);
	cpSolver->SetLowerBox(lower);
	cpSolver->SetUpperBox(upper);

	cpSolver->Minimize();

	delete cpSolver;
}

int main()
{
	test1(100);
	return 0;
	
	
}
