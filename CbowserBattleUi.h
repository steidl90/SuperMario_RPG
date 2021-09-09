#pragma once
class CbowserBattleUi
{
private:

public:
	CbowserBattleUi();
	~CbowserBattleUi();

	HRESULT init();
	void release();
	void update();
	void render(int hp, int maxhp);
};