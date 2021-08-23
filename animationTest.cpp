#include "framework.h"
#include "animationTest.h"

animationTest::animationTest()
{
}

animationTest::~animationTest()
{
}

HRESULT animationTest::init()
{

	_camel = new camel;
	_camel->init();
	return S_OK;
}

void animationTest::release()
{
	SAFE_DELETE(_camel);
}

void animationTest::update()
{
	_camel->update();
}

void animationTest::render()
{
	_camel->render();
}