#pragma once
#include "Cenemy.h"
#include "Cplayer.h"
#include "CenemyAttack.h"
#include "gameNode.h"

//enemy 행동패턴용도
enum class ENEMYTYPE {
	ENEMYTYPE_A,
	ENEMYTYPE_B,
	ENEMYTYPE_C,
	ENEMYTYPE_D,
	ENEMYTYPE_E
};

class CenemyManager : public gameNode
{
private:
	//typedef vector<Cenemy*> vEnemy;

	vector<Cenemy*>  m_vEnemy;
	vector<Cenemy*>::iterator  m_viEnemy;
	Cplayer* m_player;
	CenemyAttack* m_skill;
	float m_angle;
	int m_hitCount;
	int m_deathCount;

public:

	CenemyManager();
	~CenemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void registerEnemy(Cenemy* enemy);
	void removeMinion(int arrNum);

	void collision();
	void setPlayer(Cplayer* player) { m_player= player; }
	Cplayer* getPlayer() { return m_player; }

	// 추가
	vector<Cenemy*>* getEnemy() { return &m_vEnemy; }
};

