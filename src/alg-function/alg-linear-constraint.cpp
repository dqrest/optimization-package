#include "alg-linear-constraint.h"

template<typename T>
AlgLinearConstraint<T>::AlgLinearConstraint(): AlgLinearFunction<T>()
{

}

template<typename T>
AlgLinearConstraint<T>::AlgLinearConstraint(vector<T> v, T b): AlgLinearFunction<T>(v)
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