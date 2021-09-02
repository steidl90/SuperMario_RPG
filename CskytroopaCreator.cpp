#include "framework.h"
#include "CskytroopaCreator.h"

CskytroopaProduct* CskytroopaCreator::createProduct()
{
	return new CskytroopaProduct();
}
