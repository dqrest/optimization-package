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
	if (&constraints == NULL) {
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
CuttingPlaneMethodWithFeasibleSetApproximationSolver<T>::CuttingPlaneMethodWithFeasibleSetApproximationSolver(unsigned int dimension, T epsilon) : OptimizationSolver<T>(dimension, epsilon) {}

template<typename T>
CuttingPlaneMethodWithFeasibleSetApproximationSolver<T>::~CuttingPlaneMethodWithFeasibleSetApproximationSolver() {}

template<typename T>
bool CuttingPlaneMethodWithFeasibleSetApproximationSolver<T>::IsStopped()
{	
	T sum = T();
	for (size_t i = 0; i < this->dimension; i++)
		sum += (this->currPoint[i] - this->prevPoint[i]) * (this->currPoint[i] - this->prevPoint[i]);
	cout << "\ncurrPoint: ";
	for (size_t i = 0; i < this->dimension; i++)
		cout << this->currPoint[i] << " ";
	cout << "\nprevPoint: ";
	for (size_t i = 0; i < this->dimension; i++)
		cout << this->prevPoint[i] << " ";
	cout << "\ndistance: " << sqrt(sum);
	return sqrt(sum) <= this->eps;


	
	cout << "\ncurr: " << this->currValue << "  prev: " << this->prevValue << " eps: " << this->eps;
	cout << "abs: " << abs(this->currValue - this->prevValue);
	return abs(this->currValue - this->prevValue) <= this->eps;
}

template<typename T>
vector<size_t> CuttingPlaneMethodWithFeasibleSetApproximationSolver<T>::GetActiveConstraintsToCut(vector<T> point)
{
	vector<size_t> idx = {};
	size_t size = this->constraints.size();
	for (size_t i = 0; i < size; i++) {		
		if (!this->constraints[i]->BelongsTo(point)) 			
			idx.push_back(i);		
	}
	return idx;
}

template<typename T>
void CuttingPlaneMethodWithFeasibleSetApproximationSolver<T>::CreateCuttingPlane(vector<T> point, AlgConstraint<T>* constraint)
{
	
}

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

	do
	{
		this->prevPoint.clear();
		for (size_t i = 0; i < this->dimension; i++)
			this->prevPoint.push_back(this->currPoint[i]);
		this->prevPoint = this->currPoint;
		this->prevValue = this->currValue;

		real_1d_array x;
		minlpoptimize(state);
		minlpresults(state, x, rep);

		//cout << x.tostring(3).c_str();
		this->currPoint.clear();
		for (size_t i = 0; i < this->dimension; i++)
			this->currPoint.push_back(x[i]);
		this->currValue = this->objectiveFunction->ValueAt(this->currPoint);
		vector<size_t> activeSets = this->GetActiveConstraintsToCut(this->currPoint);
		if (activeSets.size() == 0) 
			break;

		// create cutting plane
		for (size_t i = 0; i < activeSets.size(); i++) {
			AlgConstraint<T>* constr = this->constraints[activeSets[i]];
			vector<T> point = this->currPoint;

			vector<T> s = constr->SubgradientAt(point);
			T fb = constr->ValueAt(point);
			T sx = innerProduct(point, constr->SubgradientAt(point));
			T b = innerProduct(point, constr->SubgradientAt(point)) - constr->ValueAt(point);

			ae_int_t* a = new ae_int_t[this->dimension];
			for (size_t ai = 0; ai < this->dimension; ai++)
				a[ai] = ai;

			integer_1d_array idx;
			idx.setcontent(this->dimension, a);		

			real_1d_array vala;
			vala.setcontent(this->dimension, &constr->SubgradientAt(point)[0]);
			minlpaddlc2(state, idx, vala, 2, -HUGE_VAL, b);
		}		
	} while (!this->IsStopped());

	cout << "\nsolution: ";
	for (size_t i = 0; i < this->dimension; i++)
		cout << this->currPoint[i] << " ";


	
}