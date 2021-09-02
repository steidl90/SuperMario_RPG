#pragma once
#include "Cproduct.h"
class CskytroopaProduct :public Cproduct
{
private:

public:
	using Cproduct::Cproduct;
	virtual ~CskytroopaProduct() = default;

	virtual void doStuff() override;
};

