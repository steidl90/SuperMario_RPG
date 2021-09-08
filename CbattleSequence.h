#pragma once
#include "singleton.h"
class CbattleSequence :public Singleton<CbattleSequence>
{
private:
	vector<int> vSequence;

public:
	CbattleSequence();
	~CbattleSequence() = default;

	HRESULT init();
	void pushSequence(int num);
	void remover();
	void remover(int num);

	vector<int> getVecSequence() { return vSequence; }
};

