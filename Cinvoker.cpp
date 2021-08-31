#include "framework.h"
#include "Cinvoker.h"
#include "CcommandA.h"
#include "CcommandB.h"
#include "CcommandX.h"
#include "CcommandY.h"

Cinvoker::Cinvoker() :m_commandA(new CcommandA()), m_commandB(new CcommandB()), m_commandX(new CcommandX()), m_commandY(new CcommandY())
{
}

Cinvoker::~Cinvoker()
{
	SAFE_DELETE(m_commandA);
	SAFE_DELETE(m_commandB);
	SAFE_DELETE(m_commandX);
	SAFE_DELETE(m_commandY);
}

Ccommand* Cinvoker::buttonInput()
{
	if (InputManager->isOnceKeyDown('A')) return m_commandA;
	if (InputManager->isOnceKeyDown('B')) return m_commandB;
	if (InputManager->isOnceKeyDown('X')) return m_commandX;
	if (InputManager->isOnceKeyDown('Y')) return m_commandY;

	return NULL;
}
