#pragma once
#include "gameNode.h"
class Cunit :public gameNode
{
private:
	/*
	플레이어, 이너미들이 공통으로 필요한 부분은 여기에 만들어라
	플레이어, 이너미들이 공통으로 필요한 부분은 여기에 만들어라
	플레이어, 이너미들이 공통으로 필요한 부분은 여기에 만들어라
	*/
	int m_atk;
	int m_def;
	int m_hp;
	int m_mp;
	int m_critical;
	int m_lv;
	int m_exp;
	int m_gold;
	float m_criticalAtk;
	float m_speed;


public:
	Cunit();
	~Cunit();

	HRESULT init();
	void release();
	void update();
	void render();

	//============== get ==============//
	int getAtk() { return m_atk; }
	int getDef() { return m_def; }
	int getHp() { return m_hp; }
	int getMp() { return m_mp; }
	int getCritical() { return m_critical; }
	int getLv() { return m_lv; }
	int getExp() { return m_exp; }
	int getGold() { return m_gold; }
	float getCriticalAtk() { return m_criticalAtk; }
	float getSpeed() { return m_speed; }

	//============== set ==============//

	void setAtk(int atk) { m_atk = atk; }
	void setDef(int def) { m_def = def; }
	void setHp(int hp) { m_hp = hp; }
	void setMp(int mp) { m_mp = mp; }
	void setCritical(int cri) { m_critical = cri; }
	void setLv(int lv) { m_lv = lv; }
	void setExp(int exp) { m_exp = exp; }
	void setGold(int gold) { m_gold = gold; }
	void setCriticalAtk(float criAtk) { m_criticalAtk = criAtk; }
	void setSpeed(float speed) { m_speed = speed; }

};

