#pragma once
#include "Cstate.h"
class goomba_Idle :public Cstate
{
private:
	int m_timer;
public:
	goomba_Idle();
	~goomba_Idle();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class goomba_Move :public Cstate
{
private:
	int m_timer;
public:
	goomba_Move();
	~goomba_Move();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};
