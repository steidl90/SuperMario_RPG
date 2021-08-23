#pragma once
#include "Cunit.h"

enum class STATE
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	IDLE
};

class CaStar;
class Cenemy : public Cunit
{
protected:
	class Cplayer* m_player;
	CaStar* m_aStar;
	ATTRIBUTE* m_attribute;

	image* m_walkImage;
	animation* m_walkAni;
	RECT m_walkRc;

	image* m_dieImage;
	animation* m_dieAni;
	RECT m_dieRc;

	effect* m_effect;
	STATE m_state;
	RECT m_traceRc;	

	RECT m_astarRc;

	list<POINT> m_currentAStar;
	list<POINT>::iterator m_liAstar;

	

	//임시변수
	float x, y;
	//임시변수

	float m_x, m_y;
	float m_returnX, m_returnY;
	float m_trace;
	float m_speed;
	float m_distance;
	float m_hp;
	float m_def;
	float m_maxHp;
	float m_damage;
	int m_exp;

	bool m_isIdle;
	bool m_isWalking;
	bool m_isAttack;
	bool m_isDie;

	bool isDetect;
	bool isAstarStart;
	bool isAstarSet;

	bool isSetAstar;

	int m_cooltimeCount;
	int m_rndskillCount;

public:
		class CenemyAttack* m_enemyAttack;
	Cenemy();
	~Cenemy();

	virtual HRESULT init(POINT position,float HP,float damage, float exp,float trace);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void attack();

	virtual void die();
	virtual void animation();
	virtual bool enemyCooltime();

	virtual void ReturnIdleAnimation();

	float getHp() { return m_hp; }
	void setHp(float hp) { m_hp = hp; }

	float getDamage() { return m_damage; }
	void setDamage(float damage) { m_damage = damage; }

	int getDef() { return m_def; }
	void setDef(int def) { m_def = def; }

	int getExp() { return m_exp; }
	void setExp(int exp) { m_exp = exp; }

	int getX() { return m_x; }
	int getY() { return m_y; }

	virtual void setPlayer(Cplayer* player) { m_player = player; }
	virtual RECT getRect() { return m_walkRc; }
	void setAttribute(ATTRIBUTE* att) { m_attribute = att; }

	void setAstarRoot(list<POINT> list) { m_currentAStar = list; }
	void aStarMove();

};

