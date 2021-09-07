#pragma once
#include "Cstate.h"
class CmonsterManager;
class player_Battle_Idle: public Cstate
{
private:
	RECT temp;
public:
	player_Battle_Idle();
	~player_Battle_Idle();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class player_MyTurn : public Cstate
{
private:
	RECT temp;
public:
	player_MyTurn();
	~player_MyTurn();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class player_Attack : public Cstate
{
private:
	RECT temp;
public:
	player_Attack();
	~player_Attack();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class player_Item : public Cstate
{
private:
public:
	player_Item();
	~player_Item();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class player_Skill : public Cstate
{
private:
public:
	player_Skill();
	~player_Skill();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class player_ETC : public Cstate
{
private:
public:
	player_ETC();
	~player_ETC();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class player_Run : public Cstate
{
private:
public:
	player_Run();
	~player_Run();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class player_Defence : public Cstate
{
private:
public:
	player_Defence();
	~player_Defence();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};