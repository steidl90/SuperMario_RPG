#pragma once
class CpeachBattleUi
{
private:

public:
	CpeachBattleUi();
	~CpeachBattleUi();

	HRESULT init();
	void release();
	void update();
	void render(int hp, int maxhp);
};
