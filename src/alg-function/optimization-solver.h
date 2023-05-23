#ifndef _optimization_solver_h
#define _optimization_solver_h

#include "alg-function.h"
#include "alg-constraint.h"
#include <vector>

using namespace std;

template<typename T>
class OptimizationSolver
{
private:
	unsigned int dimension;
	T eps;
	AlgFunction<T>* objectiveFunction;
	vector<AlgConstraint<T>*> constraints;
	vector<T> currPoint, prevPoint;
	T currValue, prevValue;
public:	
	OptimizationSolver(unsigned int dimension, T epsilon);
	virtual ~OptimizationSolver();
	void SetObjectiveFunction(AlgFunction<T>* objectiveFunction);
	void SetConstraints(vector<AlgConstraint<T>*> constraints);
};

template<typename T>
class CuttingPlaneMethodWithFeasibleSetApproximationSolver : public OptimizationSolver<T>
{
public:
	CuttingPlaneMethodWithFeasibleSetApproximationSolver(unsigned int dimension, T epsilon);
	~CuttingPlaneMethodWithFeasibleSetApproximationSolver();
};





#endif // !_optimization_solver_h