#pragma once
#include "Ccreator.h"
#include "CgoombaProduct.h"
class CgoombaCreator :public Ccreator
{
private:

public:
	using Ccreator::Ccreator;
	virtual ~CgoombaCreator() = default;

	// 함수의 반환형은 오버로딩 조건이 아니기 때문에 오버라이딩으로 인식된다
	virtual CgoombaProduct* createProduct() override;
};

