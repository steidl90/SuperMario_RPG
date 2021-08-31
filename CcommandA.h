#pragma once
#include "Ccommand.h"
class CcommandA :public Ccommand
{
private:

public:

	virtual void execute(Cmario& m_mario);
	virtual void undo(){}
};