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

	void vecSort();

	vector<int> getVecSequence() { return vSequence; }
};

