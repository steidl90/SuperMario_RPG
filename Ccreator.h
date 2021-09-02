#pragma once
#include "Cproduct.h"
class Ccreator
{
private:

public:
	Ccreator() = default;
	virtual ~Ccreator() = default;

	virtual Cproduct* createProduct() abstract;
	void someOperation(){}
};

