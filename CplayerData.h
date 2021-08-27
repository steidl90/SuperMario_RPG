#pragma once
#include"singleton.h"

class Citem;
class CplayerData : public Singleton<CplayerData>
{
private:
	int m_atk;
	int m_def;
	int m_hp;
	int m_maxHp;
	int m_mp;
	int m_maxMp;
	int m_critical;
	int m_lv;
	int m_exp;
	int m_gold;
	float m_criticalAtk;
	float m_speed;
	float m_x;
	float m_y;



public:
	CplayerData();
	~CplayerData();

	HRESULT init();
	void release();
	void update();
	void render();

	void setData(int atk, int def, int hp, int maxhp, int mp, int maxmp, int cri, int lv, int exp, int gold, float criatk, float speed, float x, float y);

	int getAtk() { return m_atk; }
	int getDef() { return m_def; }
	int getHp() { return m_hp; }
	int getMaxHp() { return m_maxHp; }
	int getMp() { return m_mp; }
	int getMaxMp() { return m_maxMp; }
	int getCritical() { return m_critical; }
	int getLv() { return m_lv; }
	int getExp() { return m_exp; }
	int getGold() { return m_gold; }
	float getCriticalAtk() { return m_criticalAtk; }
	float getSpeed() { return m_speed; }
	float getX() { return m_x; }
	float getY() { return m_y; }
};