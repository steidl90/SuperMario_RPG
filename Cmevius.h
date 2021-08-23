#pragma once
#include "Cunit.h"
#include "CenemyManager.h"
#include "Cplayer.h"
#include "CprogressBar.h"

enum class BOSS_STATE
{
	BOSS_STATE_IDLE,
	BOSS_STATE_WALKING,
	BOSS_STATE_CASTING,
	BOSS_STATE_LEVITATING,
	BOSS_STATE_DIE
};
class CdropItem;
class Cmevius :public Cunit
{
private:
	
	CdropItem* m_dropItem;

	CprogressBar* m_hpBar;
	image* m_meviusImage;
	animation* m_meviusAnimation;
	effect* m_meviusEffect;
	BOSS_STATE m_meviusState;

	CenemyManager* m_em;
	Cplayer* m_player;
	CenemyAttack* m_attack;

	RECT m_meviusRc;		//���� �̹��� RC
	RECT m_meviusSkillRc;	//���� ��ų RC(���ð�)
	RECT m_meviusCallRc;	//���� ��ȯ �ν� ���� RC
	RECT m_meviusDamageRc;	//���� Ÿ�� RC

	float m_x, m_y;
	float m_speed;
	float m_angle;

	float m_maxHp;
	float m_hp;
	float m_def;
	float m_exp;
	float m_skillDamagePattern1;
	float m_skillDamagePattern2;
	float m_skillDamagePattern3;

	int m_effectCount;
	int m_ActionCount;
	int m_coolTime[3];
	int m_skillCount[3];

	bool m_isEffect;		//����Ʈ����
	bool m_isTeleport;		//�ڷ���Ʈ����
	bool m_isAppear;		//�������
	bool m_isLevitating;	//���ִ� ����
	bool m_isWalking;		//�ȴ»���
	bool m_isCasting;		//ĳ���û���
	bool m_isIdle;			//�Ϲݻ���
	bool m_isDie;			//��������

public:
	Cmevius();
	~Cmevius();

	HRESULT init(POINT position,int hp, float p1Damage1);
	void release();
	void update();
	void render();

	void meviusphase1();
	void meviusphase2();
	void meviusphase3();

	void collision();

	bool meviusCooltime(int ArrNum, int skillcount);

	RECT* getRect() { return &m_meviusRc; }

	float getHp() { return m_hp; }
	void setHp(int hp) { m_hp = hp; }

	void setPlayer(Cplayer* player) { m_player = player; }
	void setDropItem(CdropItem* drop) { m_dropItem = drop; }
};

