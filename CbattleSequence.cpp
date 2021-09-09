#include "framework.h"
#include "CbattleSequence.h"

CbattleSequence::CbattleSequence() :vSequence()
{
}

HRESULT CbattleSequence::init()
{
	return S_OK;
}

void CbattleSequence::pushSequence(int num)
{
	vSequence.push_back(num);
	
}

void CbattleSequence::remover()
{
	vSequence.erase(vSequence.begin());
}

void CbattleSequence::remover(int num)
{
	for (int i = 0; i < vSequence.size(); i++)
	{
		if (vSequence[i] == num) {
			vSequence.erase(vSequence.begin() + i);
			break;
		}
	}
}

void CbattleSequence::vecSort()
{
	sort(vSequence.begin(), vSequence.end());
}
