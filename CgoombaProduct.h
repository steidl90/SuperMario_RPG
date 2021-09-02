#pragma once
#include "Cproduct.h"
class CgoombaProduct :public Cproduct
{
private:
	friend class CgoombaCreator;

public:
	using Cproduct::Cproduct; // 생성자 상속(부모 생성자를 쓴다는 뜻)
	virtual ~CgoombaProduct() = default;

	virtual void doStuff() override;
};

