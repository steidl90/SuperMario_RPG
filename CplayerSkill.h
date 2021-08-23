#pragma once
#include "Cunit.h"

struct tagPlayerSkill 
{
	image* m_skillImage;
	RECT m_skillRc;
	animation* m_skillAni;

	float m_skillX, m_skillY;
	float m_fireX, m_fireY;
	float m_radius;
	float m_angle;
	float m_speed;
	float m_range;
	bool m_fire;
};
enum class  SKILL
{
	SKILL_IDLE,
	SKILL_LEFT,
	SKILL_UP,
	SKILL_RIGHT,
	SKILL_DOWN
};

class Cenemy;
class CplayerSkill :public Cunit
{
private:
	SKILL skillDirection;
	Cenemy* m_enemy;
	vector<tagPlayerSkill> m_vPlayerSkill;
	vector<tagPlayerSkill>::iterator m_viPlayerSkill;

	image* playerAttackDown;
	image* playerAttackUp;
	image* playerAttackLeft;
	image* playerAttackRight;

	animation* playerAttackAni;
	animation* m_playerSkillAni;
	animation* m_playerThunderSkillAni;

	RECT m_skillRc;

public:
	CplayerSkill();
	~CplayerSkill();

	HRESULT init();
	void release();
	void update(const char* aniName);
	void render();
	void skillInformation(float x, float y, float angle, float speed, float range, const char* fileName, const char* aniName);
	void removeSkill(int arrNum);

	vector<tagPlayerSkill> getvSkill() { return m_vPlayerSkill; }

	void setEnemyMemory(Cenemy* enemy) { m_enemy = enemy; }

};

