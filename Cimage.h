#pragma once
class Cimage
{
private:

public:
	Cimage();
	~Cimage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

