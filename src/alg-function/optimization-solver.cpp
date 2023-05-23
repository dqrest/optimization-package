#include "optimization-solver.h"


template<typename T>
OptimizationSolver<T>::OptimizationSolver(unsigned int dimension, T epsilon)
{
	this->dimension = dimension;
	this->eps = epsilon;
	this->currValue = T() + epsilon;
	this->prevValue = 2 * (T() + epsilon);
	this->lowerBox = {};
	this->upperBox = {};
	for (size_t i = 0; i < dimension; i++) {
		this->currPoint.push_back(2 * (T() + epsilon));
		this->prevPoint.push_back(T() + epsilon);
		this->lowerBox.push_back(-HUGE_VAL);
		this->upperBox.push_back(HUGE_VAL);
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
void OptimizationSolver<T>::SetLowerBox(vector<T> lb)
{
	if (&lb == NULL || lb.size() != this->dimension) return;
	this->lowerBox = lb;	
}

template<typename T>
void OptimizationSolver<T>::SetUpperBox(vector<T> ub)
{
	if (&ub == NULL || ub.size() != this->dimension) return;
	this->upperBox = ub;
}

template<typename T>
CuttingPlaneMethodWithFeasibleSetApproximationSolver<T>::CuttingPlaneMethodWithFeasibleSetApproximationSolver(unsigned int dimension, T epsilon) : OptimizationSolver<T>(dimension, epsilon){}

template<typename T>
CuttingPlaneMethodWithFeasibleSetApproximationSolver<T>::~CuttingPlaneMethodWithFeasibleSetApproximationSolver(){}

template<typename T>
void CuttingPlaneMethodWithFeasibleSetApproximationSolver<T>::Minimize()
{
	real_1d_array linearObjective;
	vector<T> cv = this->objectiveFunction->SubgradientAt(this->currPoint);
	linearObjective.setcontent(this->dimension, &cv[0]);
	cout << "linearObjective: ";
	printArray(this->dimension, &cv[0]);


	real_1d_array bndl;
	bndl.setcontent(this->dimension, &this->lowerBox[0]);
	cout << "\nlowerBox: ";
	printArray(this->dimension, &this->lowerBox[0]);

	real_1d_array bndu;
	bndu.setcontent(this->dimension, &this->upperBox[0]);
	cout << "\nupperBox: ";
	printArray(this->dimension, &this->upperBox[0]);

	minlpstate state;
	minlpreport rep;



	minlpcreate(this->dimension, state);
	minlpsetcost(state, linearObjective);
	minlpsetbc(state, bndl, bndu);
	minlpsetalgodss(state, this->eps);

	real_1d_array x;
	minlpoptimize(state);
	minlpresults(state, x, rep);
	cout << x.tostring(3).c_str();

	ae_int_t *a = new ae_int_t[2]{ 0, 1 };
	integer_1d_array idx;
	idx.setcontent(this->dimension, a);

	long double* v = new long double[2]{ 1, 1 };
	real_1d_array vala;
	vala.setcontent(this->dimension, v);


	minlpaddlc2(state, idx, vala, 2, -HUGE_VAL, 1);
	minlpoptimize(state);
	minlpresults(state, x, rep);
	cout << x.tostring(3).c_str();

	while (abs(this-> currValue - this-> prevValue) > this->eps)
	{
		this->currValue = this->currValue / 2;
		this->prevValue = this->prevValue / 2;
		break;
	}
}