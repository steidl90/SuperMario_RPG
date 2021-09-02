#pragma once
#include "Cunit.h"
class Cmonster :public Cunit
{
private:
	friend class CmonsterFactory;

	using Cunit::Cunit;

public:
	virtual ~Cmonster() = default;

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void updata() = 0;
	virtual void render() = 0;

	virtual void attack() = 0;
	virtual void run() = 0;
};