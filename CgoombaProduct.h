#pragma once
#include "Cproduct.h"
class CgoombaProduct :public Cproduct
{
private:
	friend class CgoombaCreator;

public:
	using Cproduct::Cproduct; // ������ ���(�θ� �����ڸ� ���ٴ� ��)
	virtual ~CgoombaProduct() = default;

	virtual void doStuff() override;
};

