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
	/*OptimizationSolver<T>(AlgFunction<T>* objectiveFunction, vector<AlgConstraint<T>*> constraints);
	~OptimizationSolver<T>();*/
	OptimizationSolver(unsigned int dimension, T epsilon);
	void SetObjectiveFunction(AlgFunction<T>* objectiveFunction);
	void SetConstraints(vector<AlgConstraint<T>*> constraints);
};



#endif // !_optimization_solver_h