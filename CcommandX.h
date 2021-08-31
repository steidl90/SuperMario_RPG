#pragma once
#include "Ccommand.h"
class CcommandX :public Ccommand
{
private:

public:

	virtual void execute(Cmario& m_mario) {}
	virtual void undo() {}
};
