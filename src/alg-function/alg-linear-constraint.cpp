#include "alg-linear-constraint.h"

template<typename T>
AlgLinearConstraint<T>::AlgLinearConstraint() : AlgLinearFunction<T>()
{

}

template<typename T>
AlgLinearConstraint<T>::AlgLinearConstraint(vector<T> v, T b) : AlgLinearFunction<T>(v)
{
	this->b = b;
}

template<typename T>
void AlgLinearConstraint<T>::Print()
{
	size_t size = this->c.size();
	for (size_t i = 0; i < size; i++)
	{
		if (i > 0 && this->c[i] >= 0)
		{
			cout << "+";
		}
		cout << this->c[i] << "x[" << (i + 1) << "]";
	}
	cout << "<=" << this->b;
}

template<typename T>
void AlgLinearConstraint<T>::Inverse()
{
	AlgLinearFunction<T>::Inverse();
	this->b = -this->b;
}


template<typename T>
AlgBoxConstraint<T>::AlgBoxConstraint<T>(int dimension, int ind, vector<string> b) : AlgLinearFunction<T>()
{
	if (&b == NULL) return;
	if (ind > 0 && ind <= dimension && b.size() == 2)
	{
		this->_ind = ind;
		this->_lower = b[0];
		this->_upper = b[1];
		this->_dimension = dimension;
		return;
	}
}


template<typename T>
void AlgBoxConstraint<T>::Print()
{
	cout << this->_lower << " <= " << "x[" << this->_ind << "]" << " <= " << this->_upper;
}

template<typename T>
int AlgBoxConstraint<T>::GetInd()
{
	return this->_ind;
}

template<typename T>
double AlgBoxConstraint<T>::GetLower()
{
	return this->_lower == "-inf"
		? -HUGE_VAL
		: stod(this->_lower);
}

template<typename T>
double AlgBoxConstraint<T>::GetUpper()
{
	return this->_upper == "+inf"
		? HUGE_VAL
		: stod(this->_upper);
}
