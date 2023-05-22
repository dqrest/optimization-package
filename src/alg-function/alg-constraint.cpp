#include "alg-constraint.h"

template<typename T>
AlgConstraint<T>::AlgConstraint(AlgFunction<T>* f, T b)
{
	this->f = f;
	this->b = b;
	this->cType = EConstraintType::LE;
}

template<typename T>
void AlgConstraint<T>::PrintConstraintType()
{
	switch (this->cType)
	{
	case EConstraintType::LE:
		cout << "<=";
		break;
	case EConstraintType::RE:
		cout << ">=";
	default:
		break;
	}
}

template<typename T>
void AlgConstraint<T>::Print()
{
	if(this->f != NULL)
		this->f->Print();
	this->PrintConstraintType();
	cout << this->b;
}

template<typename T>
void AlgConstraint<T>::InverseConstraintType()
{
	switch (this->cType)
	{
	case EConstraintType::LE:
		this->cType = EConstraintType::RE;
		break;
	case EConstraintType::RE:
		this->cType = EConstraintType::LE;
	default:
		break;
	}
}

template<typename T>
void AlgConstraint<T>::Inverse()
{
	if(this->f != NULL)
		this->f->Inverse();
	this->InverseConstraintType();
	this->b = -this->b;	
}