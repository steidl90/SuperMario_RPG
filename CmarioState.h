#pragma once
#include "Cstate.h"
class player_Idle : public Cstate
{
private:
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
public:
	player_Move();
	~player_Move();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

//
//class player_Atk : public Cstate
//{
//private:
//public:
//	player_Atk();
//	~player_Atk();
//	virtual void update();
//	virtual void Enter();
//	virtual void Exit();
//};
//
//class player_Die : public Cstate
//{
//private:
//public:
//	player_Die();
//	~player_Die();
//	virtual void update();
//	virtual void Enter();
//	virtual void Exit();
//};

