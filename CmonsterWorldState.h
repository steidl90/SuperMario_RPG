#pragma once
#include "Cstate.h"
class monster_Idle :public Cstate
{
private:
	int m_timer;
public:
	monster_Idle();
	~monster_Idle();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class monster_Move :public Cstate
{
private:
	int m_timer;
public:
	monster_Move();
	~monster_Move();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class monster_Trace :public Cstate
{
private:
	int m_timer;
public:
	monster_Trace();
	~monster_Trace();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class monster_Battle :public Cstate
{
private:
	int m_timer;
public:
	monster_Battle();
	~monster_Battle();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class monster_Die :public Cstate
{
private:
	int m_timer;
public:
	monster_Die();
	~monster_Die();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};