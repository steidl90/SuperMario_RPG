#pragma once
#include "Ccreator.h"
#include "CgoombaProduct.h"
class CgoombaCreator :public Ccreator
{
private:

public:
	using Ccreator::Ccreator;
	virtual ~CgoombaCreator() = default;

	// �Լ��� ��ȯ���� �����ε� ������ �ƴϱ� ������ �������̵����� �νĵȴ�
	virtual CgoombaProduct* createProduct() override;
};

