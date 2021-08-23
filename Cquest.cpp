#include "framework.h"
#include "Cquest.h"
#include "Cplayer.h"

Cquest::Cquest()
{
	m_player = nullptr;
}

Cquest::~Cquest()
{
}

HRESULT Cquest::init()
{
	m_npc = new CNPC;
	m_dialogImage = IMAGE->findImage("대화창");
	m_dialogBGImage = IMAGE->findImage("대화창배경");
	m_buttonImage = IMAGE->findImage("버튼");

	m_x[0] = 1020;
	m_y[0] = 520;

	m_x[1] = WINSIZEX / 2 - 270;
	m_y[1] = WINSIZEY / 2 - 300;

	m_x[2] = WINSIZEX / 2 + 3;
	m_y[2] = WINSIZEY / 2 - 50;
	m_quest = 0;
	m_maxQuest = 30;


	ANIMATION->addDefAnimation("퀘스트애니", "퀘스트1", 6, false, true);
	ANIMATION->addDefAnimation("퀘스트2애니", "퀘스트2", 6, false, true);
	ANIMATION->addDefAnimation("퀘스트3애니", "퀘스트3", 1, false, true);
	m_questImage = IMAGE->findImage("퀘스트1");
	m_questAni = ANIMATION->findAnimation("퀘스트애니");
	ANIMATION->start("퀘스트애니");

	m_isDialog = false;
	m_isQuesting = false;
	m_isComplete = false;
	m_isOneTime = true;
	return S_OK;
}

void Cquest::release()
{
}

void Cquest::update()
{
	if (InputManager->isOnceKeyDown('H'))
	{
		m_quest += 5;
	}
	dialog();
	selectQuest();
	stateQuest();
	if (m_isQuesting && m_isComplete)
	{
		dialog();
	}
	if (!m_isQuesting && m_isComplete)
	{
		if (m_isOneTime)
		{
		m_player->setExp(m_player->getExp() + 100);
		m_isOneTime = false;
		}
	}
	if (m_npc != nullptr)
	{
		m_questRc = RectMake(m_x[0], m_y[0], m_questImage->getFrameWidth(), m_questImage->getFrameHeight());
		m_dialogRc = RectMake(m_x[1], m_y[1], m_dialogImage->getFrameWidth(), m_dialogImage->getFrameHeight());
		m_buttonRc = RectMake(m_x[2], m_y[2], m_buttonImage->getFrameWidth(), m_buttonImage->getFrameHeight());
	}
}

void Cquest::render()
{
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	if (m_npc != nullptr)
	{
		if (collision()&&!m_isQuesting)
		{
			m_buttonImage->render(getMemDC(), m_x[2], m_y[2]);
			TCHAR str[256];
			sprintf_s(str, "대화하기");
			TextOut(getMemDC(), m_x[2] - 20, m_y[2] + 20, str, strlen(str));
			TCHAR buttonstr[256];
			sprintf_s(buttonstr, "F");
			TextOut(getMemDC(), m_x[2] + 10, m_y[2] + 5, buttonstr, strlen(buttonstr));
			if (m_isDialog&&!m_isComplete)
			{
				m_dialogBGImage->alphaRender(getMemDC(), m_x[1], m_y[1], 200);
				IMAGE->findImage("대화텍스트")->render(getMemDC(), m_x[1], m_y[1]);
				m_dialogImage->render(getMemDC(), m_x[1], m_y[1]);
			}
			if (m_isDialog && m_isComplete)
			{
				m_dialogBGImage->alphaRender(getMemDC(), m_x[1], m_y[1], 200);
				IMAGE->findImage("일상텍스트")->render(getMemDC(), m_x[1], m_y[1]);
				m_dialogImage->render(getMemDC(), m_x[1], m_y[1]);
			}
		}
		if (!m_isComplete)
		{
		m_questImage->aniRender(getMapDC(), m_x[0], m_y[0], m_questAni);
		}
	}
	if (m_isQuesting)
	{
		m_questImage = IMAGE->findImage("퀘스트3");
		m_questAni = ANIMATION->findAnimation("퀘스트3애니");
		ANIMATION->start("퀘스트3애니");
		m_questImage->aniRender(getMapDC(), m_x[0], m_y[0], m_questAni);

		TCHAR str[256];
		sprintf_s(str, "몬스터를 처치하라!");
		TextOut(getMemDC(), WINSIZEX - 200, 280, str, strlen(str));
		if (!m_isComplete)
		{
			TCHAR queststr[256];
			sprintf_s(queststr, "몬스터 처치 \n %d / %d", m_quest, m_maxQuest);
			TextOut(getMemDC(), WINSIZEX - 200, 310, queststr, strlen(queststr));
		}
		else if (m_isComplete)
		{
			m_questImage = IMAGE->findImage("퀘스트2");
			m_questAni = ANIMATION->findAnimation("퀘스트2애니");
			ANIMATION->start("퀘스트2애니");
			m_questImage->aniRender(getMapDC(), m_x[0], m_y[0], m_questAni);

			TCHAR queststr[256];
			sprintf_s(queststr, "퀘스트 완료!");
			TextOut(getMemDC(), WINSIZEX - 200, 310, queststr, strlen(queststr));
			if (collision())
			{
				m_buttonImage->render(getMemDC(), m_x[2], m_y[2]);
				TCHAR str[256];
				sprintf_s(str, "대화하기");
				TextOut(getMemDC(), m_x[2] - 20, m_y[2] + 20, str, strlen(str));
				TCHAR buttonstr[256];
				sprintf_s(buttonstr, "F");
				TextOut(getMemDC(), m_x[2] + 10, m_y[2] + 5, buttonstr, strlen(buttonstr));
				if (m_isDialog)
				{
					m_dialogBGImage->alphaRender(getMemDC(), m_x[1], m_y[1], 200);
					IMAGE->findImage("퀘스트성공텍스트")->render(getMemDC(), m_x[1], m_y[1]);
					m_dialogImage->render(getMemDC(), m_x[1], m_y[1]);
				}
			}
		}
	}
}

bool Cquest::collision()
{
	if (m_npc != nullptr)
	{
		RECT temp;
		if (IntersectRect(&temp, m_player->getplayerMoveRC(), m_npc->getGaNorRect()))
		{
			return true;
		}
		return false;
	}
	return false;
}

void Cquest::dialog()
{
	if (collision())
	{
		if (!m_isDialog)
		{
			if (InputManager->isOnceKeyDown('F'))
			{
				m_isDialog = !m_isDialog;
			}
		}
	}
	else m_isDialog = false;
}

void Cquest::selectQuest()
{
	if (m_isDialog&&!m_isComplete)
	{
		if (InputManager->isOnceKeyDown('F'))
		{
			m_isQuesting = true;
			m_isDialog = false;
		}
		if (InputManager->isOnceKeyDown('G'))
		{
			m_isDialog = false;
		}
	}
	if (m_isQuesting && m_isComplete)
	{
		if (InputManager->isOnceKeyDown('F'))
		{
			m_isQuesting = false;
			m_isDialog = false;
		}
	}
	if (!m_isQuesting && m_isComplete)
	{
		if (InputManager->isOnceKeyDown('F'))
		{
			m_isDialog = false; 
		}
	}
}

void Cquest::stateQuest()
{
	if (!m_isQuesting&&!m_isComplete)
	{
		m_quest = 0;

	}
	if (m_isQuesting)
	{
		if (m_quest >= m_maxQuest)
		{
			m_isComplete = true;
		}
	}

}
