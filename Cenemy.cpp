#include "framework.h"
#include "Cenemy.h"
#include "Cplayer.h"
#include "CenemyAttack.h"
#include "CaStar.h"

Cenemy::Cenemy()
{
}

Cenemy::~Cenemy()
{
}

HRESULT Cenemy::init(POINT position, float HP, float damage, float exp, float trace)
{
    return S_OK;
}

void Cenemy::release()
{

}

void Cenemy::update()
{

}

void Cenemy::render()
{

}

void Cenemy::move()
{

	RECT temp;
	if (IntersectRect(&temp, m_player->getplayerMoveRC(), &m_traceRc))
	{
		if (isSetAstar)
		{
			this->aStarMove();
		}
		else
		{
			if (m_player->getplayerMoveRC()->right >= m_traceRc.left && m_player->getplayerMoveRC()->right < m_walkRc.left)
			{
				if (m_player->getplayerMoveRC()->right < m_walkRc.left - m_distance) m_x--;
				m_isWalking = true;
				m_state = STATE::LEFT;
			}
			if (m_player->getplayerMoveRC()->left <= m_traceRc.right && m_player->getplayerMoveRC()->left > m_walkRc.right)
			{
				if (m_player->getplayerMoveRC()->left > m_walkRc.right + m_distance) m_x++;
				m_isWalking = true;
				m_state = STATE::RIGHT;
			}
			if (m_player->getplayerMoveRC()->bottom >= m_traceRc.top && m_player->getplayerMoveRC()->bottom < m_walkRc.top)
			{
				if (m_player->getplayerMoveRC()->bottom < m_walkRc.top - m_distance)m_y--;
				m_isWalking = true;
				m_state = STATE::UP;
			}
			if (m_player->getplayerMoveRC()->top <= m_traceRc.bottom && m_player->getplayerMoveRC()->top > m_walkRc.bottom)
			{
				if (m_player->getplayerMoveRC()->top > m_walkRc.bottom + m_distance)m_y++;
				m_isWalking = true;
				m_state = STATE::DOWN;
			}
		}
		isDetect = true;
	}
	else
	{
		float distance = UTIL::getDistance(m_x, m_y, m_returnX, m_returnY);
		if (distance > 1)
		{
			if (isSetAstar)
			{
				this->aStarMove();
			}
			else
			{
				m_x += (m_returnX - m_x) / distance * (m_speed * 0.8);
				m_y += (m_returnY - m_y) / distance * (m_speed * 0.8);
				if (m_x <= m_returnX && abs(m_x - m_returnX) > abs(m_y - m_returnY))
				{
					m_isWalking = true;
					m_state = STATE::RIGHT;
				}
				if (m_x >= m_returnX && abs(m_x - m_returnX) > abs(m_y - m_returnY))
				{
					m_isWalking = true;

					m_state = STATE::LEFT;
				}
				if (m_y <= m_returnY && abs(m_x - m_returnX) < abs(m_y - m_returnY))
				{
					m_isWalking = true;

					m_state = STATE::DOWN;
				}
				if (m_y >= m_returnY && abs(m_x - m_returnX) < abs(m_y - m_returnY))
				{
					m_isWalking = true;

					m_state = STATE::UP;
				}
			}
		}
		else
		{
			m_x = m_returnX;
			m_y = m_returnY;
		}
		isDetect = false;
	}
	animation();
}

void Cenemy::attack()
{
}

void Cenemy::die()
{
}

void Cenemy::animation()
{

}

bool Cenemy::enemyCooltime()
{
	return false;
}

void Cenemy::ReturnIdleAnimation()
{
}

void Cenemy::aStarMove()
{

	if (m_currentAStar.size() > 0)
	{
		if (isAstarStart)
		{
			m_liAstar = m_currentAStar.begin();
			isAstarStart = false;
		}

		if (m_liAstar != m_currentAStar.end())
		{

			if (m_x < m_liAstar->x)
			{
				m_x+=2.0;
				m_isWalking = true;
				m_state = STATE::RIGHT;
			}
			else if (m_x > m_liAstar->x)
			{
				m_x-=2.0;
				m_isWalking = true;
				m_state = STATE::LEFT;
			}

			if (m_y < m_liAstar->y)
			{
				m_y+=2.0;
				m_isWalking = true;
				m_state = STATE::DOWN;

			}
			else if (m_y > m_liAstar->y)
			{
				m_y-=2.0;
				m_isWalking = true;
				m_state = STATE::UP;
			}

			x = m_liAstar->x;
			y = m_liAstar->y;

			if (m_liAstar->x < m_x + 10 && m_liAstar->x > m_x - 10
				&& m_liAstar->y < m_y + 10 && m_liAstar->y > m_y - 10)
			{
				m_liAstar++;
			}
		}
		else
		{
			//m_aStar->getFastLoadLocation()->clear();
		}
	}
}

