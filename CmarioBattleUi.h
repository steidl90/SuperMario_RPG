#pragma once
class CmarioBattleUi
{
private:

public:
	CmarioBattleUi();
	~CmarioBattleUi();

	HRESULT init();
	void release();
	void update();
	void render(int hp, int maxhp);
};

