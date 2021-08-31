#include "framework.h"
#include "CcommandA.h"

//void CcommandA::execute(Cmario& m_mario)
//{
//	if (m_mario.getisFight()) m_mario.attack();
//	else m_mario.run();
//}

void CcommandA::execute(Cunit& unit)
{
	if (unit.getisFight()) unit.attack();
	else unit.run();
}
