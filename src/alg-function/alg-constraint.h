#ifndef _alg_constraint_h
#define _alg_constraint_h

#include <vector>
#include <iostream>
#include "alg-function.h"

using namespace std;

enum EConstraintType{
	LE = 0, // left less or equal (i.e. <=)
	L = 1,  // left less (i.e. < )
	RE = 2, // right more or equal (i.e. >=)
	R = 3,  // more right (i.e. > )
	E = 4,  // equal (i.e. =)
};

template<typename T>
class AlgConstraint
{
protected:
	T b;
	AlgFunction<T>* f;
	EConstraintType cType;
public:
	AlgConstraint(AlgFunction<T>* f, T b);
	void Print();
	void PrintConstraintType();
	void Inverse();
	void InverseConstraintType();
};

#endif // !_alg_constraint_h