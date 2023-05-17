#include "alg-function.h"

template<typename T>
AlgLinearFunction<T>::AlgLinearFunction()
{

}

template<typename T>
AlgLinearFunction<T>::AlgLinearFunction(vector<T> v)
{
	this->c = v;
}

template<typename T>
vector<T> AlgLinearFunction<T>::SubgradientAt(vector<T> x)
{
	return this->c;
}

template<typename T>
T AlgLinearFunction<T>::ValueAt(vector<T> x) 
{
	T sum = T();
	int size = this->c.size();
	if (size != x.size()) return sum;
	for (int i = 0; i < size; i++)
		sum += this->c[i] * x[i];
	return sum;
}

template<typename T>
void AlgLinearFunction<T>::Print()
{
	size_t size = c.size();
	for (size_t i = 0; i < size; i++)
	{
		if (i > 0 && c[i] >= 0)		
			cout << "+";		
		cout << c[i] << "x[" << (i + 1) << "]";
	}
}

template<typename T>
void AlgLinearFunction<T>::Inverse()
{
	for (size_t i = 0; i < c.size(); i++)
		c[i] = -c[i];
}