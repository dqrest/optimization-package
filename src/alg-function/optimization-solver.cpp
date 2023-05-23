#include "optimization-solver.h"


template<typename T>
OptimizationSolver<T>::OptimizationSolver(unsigned int dimension, T epsilon)
{
	this->dimension = dimension;
	this->eps = epsilon;
	this->currValue = T();
	this->prevValue = 2 * (T() + epsilon);
	for (size_t i = 0; i < dimension; i++) {
		this->currPoint.push_back(2 * (T() + epsilon));
		this->prevPoint.push_back(T() + epsilon);
	}
}

template<typename T>
OptimizationSolver<T>::~OptimizationSolver()
{
	size_t size = this->constraints.size();
	for (size_t i = 0; i < size; i++)
		delete this->constraints[i];
	delete this->objectiveFunction;
}

template<typename T>
void OptimizationSolver<T>::SetObjectiveFunction(AlgFunction<T>* objectiveFunction)
{
	this->objectiveFunction = objectiveFunction;
}

template<typename T>
void OptimizationSolver<T>::SetConstraints(vector<AlgConstraint<T>*> constraints)
{	
	if (constraints == NULL) {
		this->constraints = {};
		return;
	}	
	this->constraints = constraints;
}


template<typename T>
CuttingPlaneMethodWithFeasibleSetApproximationSolver<T>::CuttingPlaneMethodWithFeasibleSetApproximationSolver(unsigned int dimension, T epsilon): OptimizationSolver<T>(dimension, epsilon)
{
}

template<typename T>
CuttingPlaneMethodWithFeasibleSetApproximationSolver<T>::~CuttingPlaneMethodWithFeasibleSetApproximationSolver()
{
	//OptimizationSolver<T>::~OptimizationSolver();
}