#pragma once
#include "Ccreator.h"
#include "CskytroopaProduct.h"
class CskytroopaCreator :public Ccreator
{
private:

public:
	using Ccreator::Ccreator;
	virtual ~CskytroopaCreator() = default;

	virtual CskytroopaProduct* createProduct() override;

};

