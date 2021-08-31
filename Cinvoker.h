#pragma once
#include "Ccommand.h"

class Cinvoker
{
private:
	Ccommand* m_commandA;
	Ccommand* m_commandB;
	Ccommand* m_commandX;
	Ccommand* m_commandY;
public:
	Cinvoker();
	~Cinvoker();

	Ccommand* buttonInput();
};

