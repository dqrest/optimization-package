#ifndef _optimization_solver_h
#define _optimization_solver_h

#include "optimization.h"
#include "alg-function.h"
#include "alg-constraint.h"
#include <vector>

using namespace std;
using namespace alglib;

template<typename T>
class OptimizationSolver
{
protected:
	unsigned int dimension;
	T eps;
	AlgFunction<T>* objectiveFunction;
	vector<AlgConstraint<T>*> constraints;
	vector<T> currPoint, prevPoint;
	vector<T> lowerBox, upperBox;
	T currValue, prevValue;
public:
	OptimizationSolver(unsigned int dimension, T epsilon);
	virtual ~OptimizationSolver();
	void SetObjectiveFunction(AlgFunction<T>* objectiveFunction);
	void SetConstraints(vector<AlgConstraint<T>*> constraints);
	void SetLowerBox(vector<T> lb);
	void SetUpperBox(vector<T> ub);
	virtual void Minimize() = 0;
	virtual bool IsStopped() = 0;	
};

template<typename T>
class CuttingPlaneMethodWithFeasibleSetApproximationSolver : public OptimizationSolver<T>
{
public:
	CuttingPlaneMethodWithFeasibleSetApproximationSolver(unsigned int dimension, T epsilon);
	~CuttingPlaneMethodWithFeasibleSetApproximationSolver();
	void Minimize();
	virtual bool IsStopped();
	virtual vector<size_t> GetActiveConstraintsToCut(vector<T> point);	
	virtual void CreateCuttingPlane(vector<T> point, AlgConstraint<T>* constraint);
};

template<typename T>
void printArray(size_t size, T* array)
{
	for (size_t i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
}

template<typename T>
T innerProduct(vector<T> x, vector<T> y)
{
	if (x.size() != y.size()) return T();
	T sum = T();
	for (size_t i = 0; i < x.size(); i++)
		sum += x[i] * y[i];
	return sum;
}

#endif // !_optimization_solver_h