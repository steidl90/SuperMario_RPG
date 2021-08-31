#pragma once
#include "Ccommand.h"
class CcommandB :public Ccommand
{
private:

public:
	virtual void execute(Cmario& m_mario) {}
	virtual void undo() {}
};
