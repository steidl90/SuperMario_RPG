#pragma once
class Canimation
{
private:

public:
	Canimation();
	~Canimation();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};