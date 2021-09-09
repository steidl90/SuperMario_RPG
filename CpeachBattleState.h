#pragma once
#include "Cstate.h"

class CmonsterManager;
class peach_Battle_Idle : public Cstate
{
private:
	RECT temp;
public:
	peach_Battle_Idle();
	~peach_Battle_Idle();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class peach_MyTurn : public Cstate
{
private:
	RECT temp;
public:
	peach_MyTurn();
	~peach_MyTurn();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class peach_Attack : public Cstate
{
private:
	RECT temp;
public:
	peach_Attack();
	~peach_Attack();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class peach_Item : public Cstate
{
private:
public:
	peach_Item();
	~peach_Item();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class peach_Skill : public Cstate
{
private:
public:
	peach_Skill();
	~peach_Skill();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class peach_ETC : public Cstate
{
private:
public:
	peach_ETC();
	~peach_ETC();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class peach_Run : public Cstate
{
private:
public:
	peach_Run();
	~peach_Run();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class peach_Defence : public Cstate
{
private:
public:
	peach_Defence();
	~peach_Defence();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};