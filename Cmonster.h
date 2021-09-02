#pragma once
#include "gameNode.h"
class Cmonster :public gameNode
{
private:
	friend class CmonsterFactory;
	int X;

public:
	Cmonster(int x);
	virtual ~Cmonster() = default;

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void updata() = 0;
	virtual void render() = 0;

	virtual void attack() = 0;
};