#include "framework.h"
#include "CgoombaCreator.h"

CgoombaProduct* CgoombaCreator::createProduct()
{
    return new CgoombaProduct;
}
