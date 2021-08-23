#include "framework.h"
#include "CenemyManager.h"


CenemyManager::CenemyManager(){}
CenemyManager::~CenemyManager(){}

HRESULT CenemyManager::init()
{
	return S_OK;
}

void CenemyManager::release()
{

}

void CenemyManager::update()
{
	m_hitCount++;
	for (int i = 0; i < m_vEnemy.size(); i++)
	{
		m_vEnemy[i]->update();
	}
}

void CenemyManager::render()
{
	/*CHAR str[128];
	sprintf_s(str, "몇마리 : %d", m_vEnemy.size());
	TextOut(getMemDC(), 100, 100, str, strlen(str));
	CHAR str1[128];
	sprintf_s(str1, "몇마리 : %d", m_vEnemy.capacity());
	TextOut(getMemDC(), 100, 130, str1, strlen(str1));*/
	for (int i = 0; i < m_vEnemy.size(); i++)
	{
		IMAGE->findImage("몬스터그림자")->alphaRender(getMapDC(), m_vEnemy[i]->getRect().left+3,
			m_vEnemy[i]->getRect().bottom-20,100);
	}
	for (int i = 0; i < m_vEnemy.size(); i++)
	{
		m_vEnemy[i]->render();
	}
}

void CenemyManager::registerEnemy(Cenemy* enemy)
{
	m_vEnemy.push_back(enemy);
}

void CenemyManager::removeMinion(int arrNum)
{
	Cenemy* temp = *(m_vEnemy.begin() + arrNum);
	m_vEnemy.erase(m_vEnemy.begin() + arrNum);
	delete temp;
}

void CenemyManager::collision()
{
	for (size_t i = 0; i < m_vEnemy.size(); i++)
	{
		if (!m_vEnemy[i]->m_enemyAttack->getMeleeAttack())
		{
			if (m_vEnemy[i]->m_enemyAttack)
			{
				for (size_t j = 0; j < m_vEnemy[i]->m_enemyAttack->getVSkill().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &m_vEnemy[i]->m_enemyAttack->getVSkill()[j].m_rc, m_player->getplayerMoveRC()))
					{
						if (m_vEnemy[i]->getDamage() <= m_player->getDef())
						{
							m_vEnemy[i]->m_enemyAttack->removeSkill(j);
						}
						else 
						{
							m_vEnemy[i]->m_enemyAttack->removeSkill(j);
							m_player->setHp(m_player->getHp() - (m_vEnemy[i]->getDamage() - m_player->getDef()));
						}
					}
				}
			}
		}
		else if (m_vEnemy[i]->m_enemyAttack->getMeleeAttack())
		{
			if (m_vEnemy[i]->m_enemyAttack)
			{
				for (size_t j = 0; j < m_vEnemy[i]->m_enemyAttack->getVSkill().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &m_vEnemy[i]->m_enemyAttack->getVSkill()[j].m_rc, m_player->getplayerMoveRC()))
					{

						if (m_hitCount % 75 == 0)
						{
							if (m_vEnemy[i]->getDamage() <= m_player->getDef())
							{
								m_player->setHp(m_player->getHp());
							}
							else m_player->setHp(m_player->getHp() - (m_vEnemy[i]->getDamage() - m_player->getDef()));
						}
					}
				}
			}
		}
	}
}
