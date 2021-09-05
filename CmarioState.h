#pragma once
#include "Cstate.h"
class CmonsterManager;
class player_Idle : public Cstate
{
private:
	RECT temp;
public:
	player_Idle();
	~player_Idle();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class player_Move : public Cstate
{
private:
	RECT temp;
public:
	player_Move();
	~player_Move();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class player_Battle : public Cstate
{
private:
public:
	player_Battle();
	~player_Battle();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class player_Die : public Cstate
{
private:
public:
	player_Die();
	~player_Die();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

