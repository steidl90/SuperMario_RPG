#pragma once
#include "gameNode.h"
#include "Cmario.h"
class Ccommand :public gameNode
{
private:

public:
	Ccommand() {}
	virtual ~Ccommand() {}
	virtual void execute(Cmario& m_mario) = 0;
	virtual void undo() = 0;
};