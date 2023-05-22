#include "alg-simple-quadratic-function.h"

template<typename T>
AlgSimpleQuadraticFunction<T>::AlgSimpleQuadraticFunction(vector<T> k, vector<T> a, vector<T> b): AlgFunction<T>()
{
	if (&k == NULL || &a == NULL || &b == NULL || k.size() != a.size() || a.size() != b.size()) {
		this->k = this->a = this->b = {};
		return;
	}
	this->k = k;
	this->a = a;
	this->b = b;
}

template<typename T>
vector<T> AlgSimpleQuadraticFunction<T>::SubgradientAt(vector<T> x)
{	
	vector<T> subgradient = {};
	if (&x == NULL || x.size() != this->k.size())
		return subgradient;
	for (size_t i = 0; i < this->k.size(); i++)
		subgradient.push_back(2 * this->k[i] * (this->a[i] * x[i] + this->b[i]) * this->a[i]);
	return subgradient;
}

template<typename T>
T AlgSimpleQuadraticFunction<T>::ValueAt(vector<T> x)
{
	T value = T();
	if (&x == NULL || x.size() != this->k.size())
		return value;
	for (size_t i = 0; i < this->k.size(); i++)
		value += this->k[i] * (this->a[i] * x[i] + this->b[i]) * (this->a[i] * x[i] + this->b[i]);
	return value;
}

template<typename T>
void AlgSimpleQuadraticFunction<T>::Print()
{
	for (size_t i = 0; i < this->k.size(); i++) {
		string prefixK = (i > 0 && this->k[i] >= 0)
			? "+"
			: "";		
		cout << prefixK;
		string prefixB = this->b[i] >= 0
			? "+"
			: "";
		cout << this->k[i] << "(" << this->a[i] << "x[" << i+1<< "]" << prefixB << this->b[i] << ")^2";
	}
}

template<typename T>
void AlgSimpleQuadraticFunction<T>::Inverse()
{
	for (size_t i = 0; i < this->k.size(); i++) 
		this->k[i] = -this->k[i];
}