#pragma once
#include "Cunit.h"
class Cmonster :public Cunit
{
private:
	friend class CmonsterFactory;

	using Cunit::Cunit;

public:
	virtual ~Cmonster() = default;


};