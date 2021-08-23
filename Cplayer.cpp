#include "framework.h"
#include "Cplayer.h"

Cplayer::Cplayer() :isMoving(false), isIdle(false), isAttack(false), isLive(true), isRect(false), m_maxHp(1000), m_maxMp(500), m_maxExp(100)
{
}

Cplayer::~Cplayer()
{
}

HRESULT Cplayer::init()
{
	setAtk(10);
	setDef(10);
	setHp(m_maxHp);
	setMp(m_maxMp);
	setCritical(5);
	setCriticalAtk(1.5);
	setSpeed(3.0f);
	setLv(1);
	setExp(0);
	setGold(5000);
	m_playerX = 50;
	m_playerY = WINSIZEY / 2 + 230;

	m_playerSkill = new CplayerSkill;
	m_playerSkill->init();

	m_time = 0;

	//DIRECTIONS
	direction = DIRECTIONS::DIRECTIONS_IDLE;
	beforeDirection = DIRECTIONS::DIRECTIONS_DOWN;

	//SKILL
	skillState = SKILL::SKILL_IDLE;

	//IMAGE
	playerDown = IMAGE->findImage("�÷��̾�Ʒ���");
	playerAttackDown = IMAGE->findImage("�÷��̾�Ʒ��ʰ���");
	playerMoveDown = IMAGE->findImage("�÷��̾�Ʒ��ʰȱ�");

	playerLeft = IMAGE->findImage("�÷��̾����");
	playerMoveLeft = IMAGE->findImage("�÷��̾���ʰȱ�");
	playerAttackLeft = IMAGE->findImage("�÷��̾���ʰ���");

	playerRight = IMAGE->findImage("�÷��̾������");
	playerMoveRight = IMAGE->findImage("�÷��̾�����ʰȱ�");
	playerAttackRight = IMAGE->findImage("�÷��̾�����ʰ���");

	playerUp = IMAGE->findImage("�÷��̾�����");
	playerMoveUp = IMAGE->findImage("�÷��̾����ʰȱ�");
	playerAttackUp = IMAGE->findImage("�÷��̾����ʰ���");

	//��ų
	ANIMATION->addDefAnimation("��ġ��ų�ִ�", "��ġ��ų", 15, false, true);

	ANIMATION->addDefAnimation("����â��ų", "����â������", 15, false, true);
	ANIMATION->addDefAnimation("������â��ų", "������â������", 15, false, true);
	ANIMATION->addDefAnimation("�Ʒ���â��ų", "�Ʒ���â������", 15, false, true);
	ANIMATION->addDefAnimation("����â��ų", "����â������", 15, false, true);

	playerSkillLightning = IMAGE->findImage("����Ʈ��");
	ANIMATION->addDefAnimation("����Ʈ�׾ִ�", "����Ʈ��", 10, false, true);
	playerLightningAni = ANIMATION->findAnimation("����Ʈ�׾ִ�");

	//MOVE
	ANIMATION->addDefAnimation("���ʰȱ�", "�÷��̾����ʰȱ�", 10, false, true);
	ANIMATION->addDefAnimation("�Ʒ��ʰȱ�", "�÷��̾�Ʒ��ʰȱ�", 10, false, true);
	ANIMATION->addDefAnimation("���ʰȱ�", "�÷��̾���ʰȱ�", 10, false, true);
	ANIMATION->addDefAnimation("�����ʰȱ�", "�÷��̾�����ʰȱ�", 10, false, true);

	//EFFECT

	//IDLE
	ANIMATION->addDefAnimation("����", "�÷��̾�����", 10, false, true);
	ANIMATION->addDefAnimation("�Ʒ���", "�÷��̾�Ʒ���", 10, false, true);
	ANIMATION->addDefAnimation("����", "�÷��̾����", 10, false, true);
	ANIMATION->addDefAnimation("������", "�÷��̾������", 10, false, true);

	//ATTACK
	ANIMATION->addDefAnimation("���ʰ���", "�÷��̾����ʰ���", 20, false, true);
	ANIMATION->addDefAnimation("�Ʒ��ʰ���", "�÷��̾�Ʒ��ʰ���", 20, false, true);
	ANIMATION->addDefAnimation("���ʰ���", "�÷��̾���ʰ���", 20, false, true);
	ANIMATION->addDefAnimation("�����ʰ���", "�÷��̾�����ʰ���", 20, false, true);

	//�⺻����
	playerIdleAni = ANIMATION->findAnimation("�Ʒ���");
	playerAttackAni = ANIMATION->findAnimation("�Ʒ��ʰ���");
	playerMoveAni = ANIMATION->findAnimation("�Ʒ��ʰȱ�");

	//��Ʈ
	playerMoveRc = RectMake(m_playerX, m_playerY, playerMoveDown->getFrameWidth(), playerMoveDown->getFrameHeight());
	
	isAstarMove = true;
	isSetAstar = false;
	m_index = 0;
	return S_OK;
}

void Cplayer::release()
{
	SAFE_DELETE(m_playerSkill);
}

void Cplayer::update()
{
	EFFECT->update();
	ANIMATION->resume("����Ʈ�׾ִ�");
	m_angle += 0.4;
	moveControl();
	playerLevelUp();
	playerMoveRc = RectMake(m_playerX, m_playerY, playerMoveDown->getFrameWidth() - 90, playerMoveDown->getFrameHeight() - 50);
	
	if (direction == DIRECTIONS::DIRECTIONS_LEFT) m_playerSkill->update("����â��ų");
	else if (direction == DIRECTIONS::DIRECTIONS_RIGHT) m_playerSkill->update("������â��ų");
	else if (direction == DIRECTIONS::DIRECTIONS_UP) m_playerSkill->update("����â��ų");
	else if (direction == DIRECTIONS::DIRECTIONS_DOWN) m_playerSkill->update("�Ʒ���â��ų");
}

void Cplayer::render()
{
	//playerRectangle();
	IMAGE->findImage("NPC�׸���")->alphaRender(getMapDC(), m_playerX - 1, m_playerY + 55, 100);
	
	
	playerSkillControl();
	playerSkillRender();
	m_playerSkill->render();
	if (isAttack) isAttackRender();
	else playerStateRender();
}

void Cplayer::moveControl()
{
	if (InputManager->isStayKeyDown(VK_RIGHT) && (InputManager->isStayKeyDown(VK_UP) || InputManager->isStayKeyDown(VK_DOWN)))
	{
		this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_RIGHT);
		if (InputManager->isStayKeyDown(VK_DOWN))
		{
			this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_DOWN);
		}
		if (InputManager->isStayKeyDown(VK_UP))
		{
			this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_UP);
		}
		isMoving = true;
		direction = DIRECTIONS::DIRECTIONS_RIGHT;
	}
	else if (InputManager->isStayKeyDown(VK_LEFT) && (InputManager->isStayKeyDown(VK_UP) || InputManager->isStayKeyDown(VK_DOWN)))
	{
		this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_LEFT);
		if (InputManager->isStayKeyDown(VK_DOWN))
		{
			this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_DOWN);
		}
		if (InputManager->isStayKeyDown(VK_UP))
		{
			this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_UP);
		}
		isMoving = true;
		direction = DIRECTIONS::DIRECTIONS_LEFT;
	}
	else if (InputManager->isStayKeyDown(VK_UP) && (InputManager->isStayKeyDown(VK_RIGHT) || InputManager->isStayKeyDown(VK_LEFT)))
	{
		this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_UP);
		if (InputManager->isStayKeyDown(VK_RIGHT))
		{
			this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_RIGHT);
		}
		if (InputManager->isStayKeyDown(VK_LEFT))
		{
			this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_LEFT);
		}
		isMoving = true;
		direction = DIRECTIONS::DIRECTIONS_UP;
	}
	else if (InputManager->isStayKeyDown(VK_DOWN) && (InputManager->isStayKeyDown(VK_RIGHT) || InputManager->isStayKeyDown(VK_LEFT)))
	{
		this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_DOWN);
		if (InputManager->isStayKeyDown(VK_RIGHT))
		{
			this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_RIGHT);
		}
		if (InputManager->isStayKeyDown(VK_LEFT))
		{
			this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_LEFT);
		}
		isMoving = true;
		direction = DIRECTIONS::DIRECTIONS_DOWN;
	}
	else if (InputManager->isStayKeyDown(VK_LEFT))
	{
		this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_LEFT);
		isMoving = true;
		direction = DIRECTIONS::DIRECTIONS_LEFT;
	}
	else if (InputManager->isStayKeyDown(VK_RIGHT))
	{
		this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_RIGHT);
		isMoving = true;
		direction = DIRECTIONS::DIRECTIONS_RIGHT;
	}
	else if (InputManager->isStayKeyDown(VK_UP))
	{
		this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_UP);
		isMoving = true;
		direction = DIRECTIONS::DIRECTIONS_UP;
	}
	else if (InputManager->isStayKeyDown(VK_DOWN))
	{
		this->blockCheck(getSpeed(), &playerMoveRc, DIRECTIONS::DIRECTIONS_DOWN);
		isMoving = true;
		direction = DIRECTIONS::DIRECTIONS_DOWN;
	}
	else isMoving = false;

	if (InputManager->isStayKeyDown(VK_SPACE)) isAttack = true;
	else
	{
		isAttack = false;
		playerAttackRc = RectMake(-100, -100, 0, 0); //�ӽ�? �� ���� ��� ������ �ٲ� ����
	}

	if (InputManager->isOnceKeyDown('Q') && this->getMp() > 10)
	{
		this->isAttack = true;
		setMp(getMp() - 10);
		if (direction == DIRECTIONS::DIRECTIONS_LEFT) m_playerSkill->skillInformation(m_playerX - 15, m_playerY + 33, PI, 7.0f, 700, "����â������", "����â��ų");
		else if (direction == DIRECTIONS::DIRECTIONS_RIGHT) m_playerSkill->skillInformation(m_playerX + 50, m_playerY + 33, PI2, 7.0f, 700, "������â������", "������â��ų");
		else if (direction == DIRECTIONS::DIRECTIONS_UP) m_playerSkill->skillInformation(m_playerX + 15, m_playerY - 20, PI * 0.5, 7.0f, 700, "����â������", "����â��ų");
		else if (direction == DIRECTIONS::DIRECTIONS_DOWN) m_playerSkill->skillInformation(m_playerX + 15, m_playerY + 100, PI * 1.5, 7.0f, 700, "�Ʒ���â������", "�Ʒ���â��ų");
	}
	else if (InputManager->isOnceKeyDown('W') && this->getLv() >= 3 && this->getMp() > 30)
	{
		this->setMp(getMp() - 30);
		isAttack = true;
		
		if (direction == DIRECTIONS::DIRECTIONS_LEFT)
		{
			m_playerSkill->skillInformation(m_playerX - 15, m_playerY + 33, PI * 0.95, 7.0f, 700, "����â������", "����â��ų");
			m_playerSkill->skillInformation(m_playerX - 15, m_playerY + 33, PI, 7.0f, 700, "����â������", "����â��ų");
			m_playerSkill->skillInformation(m_playerX - 15, m_playerY + 33, PI*1.05, 7.0f, 700, "����â������", "����â��ų");


		}
		else if (direction == DIRECTIONS::DIRECTIONS_RIGHT)
		{
			m_playerSkill->skillInformation(m_playerX + 50, m_playerY + 33, PI2*0.025, 7.0f, 700, "������â������", "������â��ų");
			m_playerSkill->skillInformation(m_playerX + 50, m_playerY + 33, PI2, 7.0f, 700, "������â������", "������â��ų");
			m_playerSkill->skillInformation(m_playerX + 50, m_playerY + 33, PI2* -0.025, 7.0f, 700, "������â������", "������â��ų");
		}
		else if (direction == DIRECTIONS::DIRECTIONS_UP)
		{
			m_playerSkill->skillInformation(m_playerX + 15, m_playerY - 20, PI * 0.45, 7.0f, 700, "����â������", "����â��ų");
			m_playerSkill->skillInformation(m_playerX + 15, m_playerY - 20, PI * 0.5, 7.0f, 700, "����â������", "����â��ų");
			m_playerSkill->skillInformation(m_playerX + 15, m_playerY - 20, PI * 0.55, 7.0f, 700, "����â������", "����â��ų");
		}
		else if (direction == DIRECTIONS::DIRECTIONS_DOWN)
		{
			m_playerSkill->skillInformation(m_playerX + 15, m_playerY + 100, PI * 1.45, 7.0f, 700, "�Ʒ���â������", "�Ʒ���â��ų");
			m_playerSkill->skillInformation(m_playerX + 15, m_playerY + 100, PI * 1.5, 7.0f, 700, "�Ʒ���â������", "�Ʒ���â��ų");
			m_playerSkill->skillInformation(m_playerX + 15, m_playerY + 100, PI * 1.55, 7.0f, 700, "�Ʒ���â������", "�Ʒ���â��ų");

		}
		
	}
	else if (InputManager->isStayKeyDown('E') && this->getLv() >= 7 && m_count == 0 && this->getMp() > 50)
	{
		this->setMp(getMp() - 50);
		m_count++;
		isAttack = true;
		m_time = TIME->getWorldTime();
		isRect = true;
		m_skillX = m_playerX;
		m_skillY = m_playerY;
		if (direction == DIRECTIONS::DIRECTIONS_LEFT) skillState = SKILL::SKILL_LEFT;
		else if (direction == DIRECTIONS::DIRECTIONS_RIGHT)  skillState = SKILL::SKILL_RIGHT;
		else if (direction == DIRECTIONS::DIRECTIONS_UP)  skillState = SKILL::SKILL_UP;
		else if (direction == DIRECTIONS::DIRECTIONS_DOWN) skillState = SKILL::SKILL_DOWN;
		
	}
	if (m_time + 2 < TIME->getWorldTime())
	{
		isRect = false;
		skillState = SKILL::SKILL_IDLE;
		m_count = 0;
		lightningCenterRc = RectMake(-100, -100, 0, 0);
		lightningLeftRc = RectMake(-100, -100, 0, 0);
		lightningRightRc = RectMake(-100, -100, 0, 0);
		lightningUpRc = RectMake(-100, -100, 0, 0);
		lightningDownRc = RectMake(-100, -100, 0, 0);

	}
	

	if (InputManager->isToggleKey(VK_F8)) // �����
	{
		setHp(getHp() - 1);
		setMp(getMp() - 1);
		if (getExp() < 100)setExp(getExp() + 1);
		else
		{
			setExp(0);
			setLv(getLv() + 1);
		}
	}
	playerMoveRc = RectMake(m_playerX, m_playerY, playerMoveDown->getFrameWidth() - 90, playerMoveDown->getFrameHeight() - 50);
	moveAnimation();
}

void Cplayer::moveAnimation()
{
	if (beforeDirection == direction) return;
	beforeDirection = direction;

	switch (direction)
	{
	case DIRECTIONS::DIRECTIONS_LEFT:
		if (isMoving)
		{
			playerMoveAni = ANIMATION->findAnimation("���ʰȱ�");
			ANIMATION->start("���ʰȱ�");
			playerAttackAni = ANIMATION->findAnimation("���ʰ���");
			ANIMATION->start("���ʰ���");
			isIdle = false;
		}
		break;
	case DIRECTIONS::DIRECTIONS_UP:
		if (isMoving)
		{
			playerMoveAni = ANIMATION->findAnimation("���ʰȱ�");
			ANIMATION->start("���ʰȱ�");
			playerAttackAni = ANIMATION->findAnimation("���ʰ���");
			ANIMATION->start("���ʰ���");
			isIdle = false;
		}
		break;
	case DIRECTIONS::DIRECTIONS_RIGHT:
		if (isMoving)
		{
			playerMoveAni = ANIMATION->findAnimation("�����ʰȱ�");
			ANIMATION->start("�����ʰȱ�");
			playerAttackAni = ANIMATION->findAnimation("�����ʰ���");
			ANIMATION->start("�����ʰ���");
			isIdle = false;
		}
		break;
	case DIRECTIONS::DIRECTIONS_DOWN:
		if (isMoving)
		{
			playerMoveAni = ANIMATION->findAnimation("�Ʒ��ʰȱ�");
			ANIMATION->start("�Ʒ��ʰȱ�");
			playerAttackAni = ANIMATION->findAnimation("�Ʒ��ʰ���");
			ANIMATION->start("�Ʒ��ʰ���");
			isIdle = false;
		}
		break;
	}
}

void Cplayer::playerStateRender()
{
	//Rectangle(getMapDC(), playerMoveRc.left, playerMoveRc.top, playerMoveRc.right, playerMoveRc.bottom);
	if (isMoving)
	{
		switch (direction)
		{
		case DIRECTIONS::DIRECTIONS_LEFT:
			playerMoveLeft->aniRender(getMapDC(), playerMoveRc.left - 45, playerMoveRc.top - 13, playerMoveAni);
			break;
		case DIRECTIONS::DIRECTIONS_UP:
			playerMoveUp->aniRender(getMapDC(), playerMoveRc.left - 45, playerMoveRc.top - 15, playerMoveAni);
			break;
		case DIRECTIONS::DIRECTIONS_RIGHT:
			playerMoveRight->aniRender(getMapDC(), playerMoveRc.left - 45, playerMoveRc.top - 13, playerMoveAni);
			break;
		case DIRECTIONS::DIRECTIONS_DOWN:
			playerMoveDown->aniRender(getMapDC(), playerMoveRc.left - 45, playerMoveRc.top - 13, playerMoveAni);
			break;
		}
	}
	else
	{
		switch (direction)
		{
		case DIRECTIONS::DIRECTIONS_LEFT:
			playerLeft->aniRender(getMapDC(), playerMoveRc.left - 40, playerMoveRc.top - 3, playerIdleAni);
			if (isIdle == false)
			{
				playerIdleAni = ANIMATION->findAnimation("����");
				ANIMATION->start("����");
				isIdle = true;
			}
			break;
		case DIRECTIONS::DIRECTIONS_UP:
			playerUp->aniRender(getMapDC(), playerMoveRc.left - 39, playerMoveRc.top - 4, playerIdleAni);
			if (!isIdle)
			{
				playerIdleAni = ANIMATION->findAnimation("����");
				ANIMATION->start("����");
				isIdle = true;
			}
			break;
		case DIRECTIONS::DIRECTIONS_RIGHT:
			playerRight->aniRender(getMapDC(), playerMoveRc.left - 39, playerMoveRc.top - 3, playerIdleAni);
			if (!isIdle)
			{
				playerIdleAni = ANIMATION->findAnimation("������");
				ANIMATION->start("������");
				isIdle = true;
			}
			break;
		case DIRECTIONS::DIRECTIONS_DOWN:
			playerDown->aniRender(getMapDC(), playerMoveRc.left - 39, playerMoveRc.top - 3, playerIdleAni);
			if (!isIdle)
			{
				playerIdleAni = ANIMATION->findAnimation("�Ʒ���");
				ANIMATION->start("�Ʒ���");
				isIdle = true;
			}
			break;
		case DIRECTIONS::DIRECTIONS_IDLE:
			playerDown->aniRender(getMapDC(), playerMoveRc.left - 39, playerMoveRc.top - 3, playerIdleAni);
			if (!isIdle)
			{
				playerIdleAni = ANIMATION->findAnimation("�Ʒ���");
				ANIMATION->start("�Ʒ���");
				isIdle = true;
			}
			break;
		}
	}
}

void Cplayer::isAttackRender()
{
	if (isMoving)
	{
		switch (direction)
		{
		case DIRECTIONS::DIRECTIONS_LEFT:
			playerAttackRc = RectMake(m_playerX - 99, m_playerY, 100, 40);
			playerAttackLeft->aniRender(getMapDC(), playerMoveRc.left - 98, playerMoveRc.top - 75, playerAttackAni);
			break;
		case DIRECTIONS::DIRECTIONS_UP:
			playerAttackRc = RectMake(m_playerX + 10, m_playerY - 89, 40, 90);
			playerAttackUp->aniRender(getMapDC(), playerMoveRc.left - 98, playerMoveRc.top - 76, playerAttackAni);
			break;
		case DIRECTIONS::DIRECTIONS_RIGHT:
			playerAttackRc = RectMake(m_playerX + 35, m_playerY, 100, 40);
			playerAttackRight->aniRender(getMapDC(), playerMoveRc.left - 98, playerMoveRc.top - 75, playerAttackAni);
			break;
		case DIRECTIONS::DIRECTIONS_DOWN:
			playerAttackRc = RectMake(m_playerX - 10, m_playerY + 67, 40, 90);
			playerAttackDown->aniRender(getMapDC(), playerMoveRc.left - 98, playerMoveRc.top - 75, playerAttackAni);
			break;
		}
	}
	else if (!isMoving)
	{
		switch (direction)
		{
		case DIRECTIONS::DIRECTIONS_LEFT:
			playerAttackRc = RectMake(m_playerX - 99, m_playerY, 100, 40);
			playerAttackLeft->aniRender(getMapDC(), playerMoveRc.left - 98, playerMoveRc.top - 75, playerAttackAni);
			break;
		case DIRECTIONS::DIRECTIONS_UP:
			playerAttackRc = RectMake(m_playerX + 10, m_playerY - 89, 40, 90);
			playerAttackUp->aniRender(getMapDC(), playerMoveRc.left - 98, playerMoveRc.top - 75, playerAttackAni);
			break;
		case DIRECTIONS::DIRECTIONS_RIGHT:
			playerAttackRc = RectMake(m_playerX + 35, m_playerY, 100, 40);
			playerAttackRight->aniRender(getMapDC(), playerMoveRc.left - 98, playerMoveRc.top - 75, playerAttackAni);
			break;
		case DIRECTIONS::DIRECTIONS_DOWN:
			playerAttackRc = RectMake(m_playerX - 10, m_playerY + 67, 40, 90);
			playerAttackDown->aniRender(getMapDC(), playerMoveRc.left - 98, playerMoveRc.top - 75, playerAttackAni);
			break;
		}
	}
}

void Cplayer::playerLevelUp()
{
	if (getExp() >= 100)
	{
		setExp(0);
		setLv(getLv() + 1);
		m_maxHp += 50;
		setHp(m_maxHp);
		m_maxMp += 20;
		setMp(getMp() + 50);
		if (getMp() > m_maxMp) setMp(m_maxMp);
	}
}

void Cplayer::playerSkillControl()
{
	if (isRect && skillState == SKILL::SKILL_LEFT)
	{
		lightningCenterRc = RectMake(m_skillX - 300, m_skillY+48, 36, 36);
		lightningLeftRc = RectMake(m_skillX - 336, m_skillY+48, 36, 36);
		lightningRightRc = RectMake(m_skillX - 264, m_skillY+48, 36, 36);
		lightningUpRc = RectMake(m_skillX - 300, m_skillY+12, 36, 36);
		lightningDownRc = RectMake(m_skillX - 300, m_skillY + 84, 36, 36);	
	}

	else if (isRect && skillState == SKILL::SKILL_RIGHT)
	{
		lightningCenterRc = RectMake(m_skillX + 300, m_skillY+48, 36, 36);
		lightningLeftRc = RectMake(m_skillX + 264, m_skillY+48, 36, 36);
		lightningRightRc = RectMake(m_skillX + 336, m_skillY+48, 36, 36);
		lightningUpRc = RectMake(m_skillX + 300, m_skillY+12, 36, 36);
		lightningDownRc = RectMake(m_skillX + 300, m_skillY + 84, 36, 36);
		
	}
	else if (isRect&& skillState == SKILL::SKILL_UP)
	{
		lightningCenterRc = RectMake(m_skillX, m_skillY - 250, 36, 36);
		lightningLeftRc = RectMake(m_skillX - 36, m_skillY - 250, 36, 36);
		lightningRightRc = RectMake(m_skillX + 36, m_skillY - 250, 36, 36);
		lightningUpRc = RectMake(m_skillX, m_skillY - 286, 36, 36);
		lightningDownRc = RectMake(m_skillX, m_skillY - 214, 36, 36);
		
	}
	else if (isRect && skillState == SKILL::SKILL_DOWN)
	{
		lightningCenterRc = RectMake(m_skillX, m_skillY + 250, 36, 36);
		lightningLeftRc = RectMake(m_skillX - 36, m_skillY + 250, 36, 36);
		lightningRightRc = RectMake(m_skillX + 36, m_skillY + 250, 36, 36);
		lightningUpRc = RectMake(m_skillX, m_skillY + 214, 36, 36);
		lightningDownRc = RectMake(m_skillX, m_skillY + 286, 36, 36);
		
	}
	
}

void Cplayer::playerSkillRender()
{
	switch (skillState)
	{
	case SKILL::SKILL_IDLE:
		break;
	case SKILL::SKILL_LEFT:
		//�߾�
		playerSkillLightning->aniRender(getMapDC(), lightningCenterRc.left + (lightningCenterRc.right - lightningCenterRc.left) / 2 - 36,
			lightningCenterRc.top + (lightningCenterRc.bottom - lightningCenterRc.top) / 2 - 402, playerLightningAni);
		//����
		playerSkillLightning->aniRender(getMapDC(), lightningLeftRc.left + (lightningLeftRc.right - lightningLeftRc.left) / 2 - 36,
			lightningLeftRc.top + (lightningLeftRc.bottom - lightningLeftRc.top) / 2 - 402, playerLightningAni);
		//������
		playerSkillLightning->aniRender(getMapDC(), lightningRightRc.left + (lightningRightRc.right - lightningRightRc.left) / 2 - 36,
			lightningRightRc.top + (lightningRightRc.bottom - lightningRightRc.top) / 2 - 402, playerLightningAni);
		//����
		playerSkillLightning->aniRender(getMapDC(), lightningUpRc.left + (lightningUpRc.right - lightningUpRc.left) / 2 - 36,
			lightningUpRc.top + (lightningUpRc.bottom - lightningUpRc.top) / 2 - 402, playerLightningAni);
		//�Ʒ���
		playerSkillLightning->aniRender(getMapDC(), lightningDownRc.left + (lightningDownRc.right - lightningDownRc.left) / 2 - 36,
			lightningDownRc.top + (lightningDownRc.bottom - lightningDownRc.top) / 2 - 402, playerLightningAni);
		break;
	case SKILL::SKILL_UP:
		//�߾�
		playerSkillLightning->aniRender(getMapDC(), lightningCenterRc.left + (lightningCenterRc.right - lightningCenterRc.left) / 2 - 36,
			lightningCenterRc.top + (lightningCenterRc.bottom - lightningCenterRc.top) / 2 - 402, playerLightningAni);
		//����
		playerSkillLightning->aniRender(getMapDC(), lightningLeftRc.left + (lightningLeftRc.right - lightningLeftRc.left) / 2 - 36,
			lightningLeftRc.top + (lightningLeftRc.bottom - lightningLeftRc.top) / 2 - 402, playerLightningAni);
		//������
		playerSkillLightning->aniRender(getMapDC(), lightningRightRc.left + (lightningRightRc.right - lightningRightRc.left) / 2 - 36,
			lightningRightRc.top + (lightningRightRc.bottom - lightningRightRc.top) / 2 - 402, playerLightningAni);
		//����
		playerSkillLightning->aniRender(getMapDC(), lightningUpRc.left + (lightningUpRc.right - lightningUpRc.left) / 2 - 36,
			lightningUpRc.top + (lightningUpRc.bottom - lightningUpRc.top) / 2 - 402, playerLightningAni);
		//�Ʒ���
		playerSkillLightning->aniRender(getMapDC(), lightningDownRc.left + (lightningDownRc.right - lightningDownRc.left) / 2 - 36,
			lightningDownRc.top + (lightningDownRc.bottom - lightningDownRc.top) / 2 - 402, playerLightningAni);
		break;
	case SKILL::SKILL_RIGHT:
		//�߾�
		playerSkillLightning->aniRender(getMapDC(), lightningCenterRc.left + (lightningCenterRc.right - lightningCenterRc.left) / 2 - 36,
			lightningCenterRc.top + (lightningCenterRc.bottom - lightningCenterRc.top) / 2 - 402, playerLightningAni);
		//����
		playerSkillLightning->aniRender(getMapDC(), lightningLeftRc.left + (lightningLeftRc.right - lightningLeftRc.left) / 2 - 36,
			lightningLeftRc.top + (lightningLeftRc.bottom - lightningLeftRc.top) / 2 - 402, playerLightningAni);
		//������
		playerSkillLightning->aniRender(getMapDC(), lightningRightRc.left + (lightningRightRc.right - lightningRightRc.left) / 2 - 36,
			lightningRightRc.top + (lightningRightRc.bottom - lightningRightRc.top) / 2 - 402, playerLightningAni);
		//����
		playerSkillLightning->aniRender(getMapDC(), lightningUpRc.left + (lightningUpRc.right - lightningUpRc.left) / 2 - 36,
			lightningUpRc.top + (lightningUpRc.bottom - lightningUpRc.top) / 2 - 402, playerLightningAni);
		//�Ʒ���
		playerSkillLightning->aniRender(getMapDC(), lightningDownRc.left + (lightningDownRc.right - lightningDownRc.left) / 2 - 36,
			lightningDownRc.top + (lightningDownRc.bottom - lightningDownRc.top) / 2 - 402, playerLightningAni);
		break;
	case SKILL::SKILL_DOWN:
		//�߾�
		playerSkillLightning->aniRender(getMapDC(), lightningCenterRc.left + (lightningCenterRc.right - lightningCenterRc.left) / 2 - 36,
			lightningCenterRc.top + (lightningCenterRc.bottom - lightningCenterRc.top) / 2 - 402, playerLightningAni);
		//����
		playerSkillLightning->aniRender(getMapDC(), lightningLeftRc.left + (lightningLeftRc.right - lightningLeftRc.left) / 2 - 36,
			lightningLeftRc.top + (lightningLeftRc.bottom - lightningLeftRc.top) / 2 - 402, playerLightningAni);
		//������
		playerSkillLightning->aniRender(getMapDC(), lightningRightRc.left + (lightningRightRc.right - lightningRightRc.left) / 2 - 36,
			lightningRightRc.top + (lightningRightRc.bottom - lightningRightRc.top) / 2 - 402, playerLightningAni);
		//����
		playerSkillLightning->aniRender(getMapDC(), lightningUpRc.left + (lightningUpRc.right - lightningUpRc.left) / 2 - 36,
			lightningUpRc.top + (lightningUpRc.bottom - lightningUpRc.top) / 2 - 402, playerLightningAni);
		//�Ʒ���
		playerSkillLightning->aniRender(getMapDC(), lightningDownRc.left + (lightningDownRc.right - lightningDownRc.left) / 2 - 36,
			lightningDownRc.top + (lightningDownRc.bottom - lightningDownRc.top) / 2 - 402, playerLightningAni);
		break;
	default:
		break;
	}
}

void Cplayer::playerRectangle()
{
	//ATTACK
	Rectangle(getMapDC(), playerAttackRc.left, playerAttackRc.top, playerAttackRc.right, playerAttackRc.bottom);
	//MOVE
	Rectangle(getMapDC(), playerMoveRc.left, playerMoveRc.top, playerMoveRc.right, playerMoveRc.bottom);
	//LIGHTNING
	Rectangle(getMapDC(), lightningCenterRc.left, lightningCenterRc.top, lightningCenterRc.right, lightningCenterRc.bottom);
	Rectangle(getMapDC(), lightningLeftRc.left, lightningLeftRc.top, lightningLeftRc.right, lightningLeftRc.bottom);
	Rectangle(getMapDC(), lightningRightRc.left, lightningRightRc.top, lightningRightRc.right, lightningRightRc.bottom);
	Rectangle(getMapDC(), lightningUpRc.left, lightningUpRc.top, lightningUpRc.right, lightningUpRc.bottom);
	Rectangle(getMapDC(), lightningDownRc.left, lightningDownRc.top, lightningDownRc.right, lightningDownRc.bottom);

	/*Rectangle(getMapDC(), lightningCenterRc.left, lightningCenterRc.top, lightningCenterRc.right, lightningCenterRc.bottom);
	Rectangle(getMapDC(), lightningLeftRc.left, lightningLeftRc.top, lightningLeftRc.right, lightningLeftRc.bottom);
	Rectangle(getMapDC(), lightningRightRc.left, lightningRightRc.top, lightningRightRc.right, lightningRightRc.bottom);
	Rectangle(getMapDC(), lightningUpRc.left, lightningUpRc.top, lightningUpRc.right, lightningUpRc.bottom);
	Rectangle(getMapDC(), lightningDownRc.left, lightningDownRc.top, lightningDownRc.right, lightningDownRc.bottom);

	Rectangle(getMapDC(), lightningCenterRc.left, lightningCenterRc.top, lightningCenterRc.right, lightningCenterRc.bottom);
	Rectangle(getMapDC(), lightningLeftRc.left, lightningLeftRc.top, lightningLeftRc.right, lightningLeftRc.bottom);
	Rectangle(getMapDC(), lightningRightRc.left, lightningRightRc.top, lightningRightRc.right, lightningRightRc.bottom);
	Rectangle(getMapDC(), lightningUpRc.left, lightningUpRc.top, lightningUpRc.right, lightningUpRc.bottom);
	Rectangle(getMapDC(), lightningDownRc.left, lightningDownRc.top, lightningDownRc.right, lightningDownRc.bottom);

	Rectangle(getMapDC(), lightningCenterRc.left, lightningCenterRc.top, lightningCenterRc.right, lightningCenterRc.bottom);
	Rectangle(getMapDC(), lightningLeftRc.left, lightningLeftRc.top, lightningLeftRc.right, lightningLeftRc.bottom);
	Rectangle(getMapDC(), lightningRightRc.left, lightningRightRc.top, lightningRightRc.right, lightningRightRc.bottom);
	Rectangle(getMapDC(), lightningUpRc.left, lightningUpRc.top, lightningUpRc.right, lightningUpRc.bottom);
	Rectangle(getMapDC(), lightningDownRc.left, lightningDownRc.top, lightningDownRc.right, lightningDownRc.bottom);*/

}

void Cplayer::blockCheck(float speed, RECT* playerRC, DIRECTIONS direct)
{
	RECT rcCollision;
	int tileIndex[2];
	rcCollision = playerMoveRc;

	int tileX;
	int tileY;

	switch (direct)
	{
	case DIRECTIONS::DIRECTIONS_LEFT:
		m_playerX -= this->getSpeed();
		rcCollision = RectMake(m_playerX, m_playerY, playerMoveDown->getFrameWidth() / 4, playerMoveDown->getFrameHeight() / 2);
		break;
	case DIRECTIONS::DIRECTIONS_UP:
		m_playerY -= this->getSpeed();
		rcCollision = RectMake(m_playerX, m_playerY, playerMoveDown->getFrameWidth() / 4, playerMoveDown->getFrameHeight() / 2);
		break;
	case DIRECTIONS::DIRECTIONS_RIGHT:
		m_playerX += this->getSpeed();
		rcCollision = RectMake(m_playerX, m_playerY, playerMoveDown->getFrameWidth() / 4, playerMoveDown->getFrameHeight() / 2);
		break;
	case DIRECTIONS::DIRECTIONS_DOWN:
		m_playerY += this->getSpeed();
		rcCollision = RectMake(m_playerX, m_playerY, playerMoveDown->getFrameWidth() / 4, playerMoveDown->getFrameHeight() / 2);
		break;
	}

	tileX = rcCollision.left / TILESIZE;
	tileY = (rcCollision.top + TILESIZE) / TILESIZE;

	switch (direct)
	{
	case DIRECTIONS::DIRECTIONS_LEFT:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY+1) * TILEX;
		break;
	case DIRECTIONS::DIRECTIONS_UP:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + 1 + tileY * TILEX;
		break;
	case DIRECTIONS::DIRECTIONS_RIGHT:
		tileIndex[0] = (tileX + tileY * TILEX) + 1;
		tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;
		break;
	case DIRECTIONS::DIRECTIONS_DOWN:
		tileIndex[0] = (tileX + tileY * TILEX) + TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
		break;
	}

	for (int i = 0; i < 2; i++)
	{
		RECT temp;
		if((m_attribute[tileIndex[i]] == ATTRIBUTE::COLLISION_ON) &&
			IntersectRect(&temp, &m_CheckTile[tileIndex[i]].rc, &rcCollision))
		{
			switch (direct)
			{
			case DIRECTIONS::DIRECTIONS_LEFT:
				playerMoveRc.left = m_CheckTile[tileIndex[i]].rc.right;
				m_playerX = playerMoveRc.left;
				break;
			case DIRECTIONS::DIRECTIONS_UP:
				playerMoveRc.top = m_CheckTile[tileIndex[i]].rc.bottom - (playerMoveRc.bottom - playerMoveRc.top)/2;
				m_playerY = playerMoveRc.top;
				break;
			case DIRECTIONS::DIRECTIONS_RIGHT:
				playerMoveRc.right = m_CheckTile[tileIndex[i]].rc.left;
				m_playerX = playerMoveRc.left;
				break;
			case DIRECTIONS::DIRECTIONS_DOWN:
				playerMoveRc.bottom = m_CheckTile[tileIndex[i]].rc.top;
				m_playerY = playerMoveRc.top;
				break;
			}
			return;
		}
	}
	//Rectangle(getMapDC(), rcCollision.left, rcCollision.top, rcCollision.right, rcCollision.bottom);
	rcCollision = RectMake(m_playerX, m_playerY, TILESIZE, TILESIZE * 2);
	playerMoveRc = rcCollision;
}

