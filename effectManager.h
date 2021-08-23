#pragma once
#include"singleton.h"

class effect;
class effectManager : public Singleton<effectManager>
{
private:
	//이펙트 클래스 담은 녀석
	typedef vector<effect*>  vEffect;
	typedef vector<effect*>::iterator viEffect;

	//이펙트 클래스가 담겨져 있는 벡터를 담은녀석
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;

	//모든 이펙트를 관리할 녀석
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;

	//실제 모든 이펙트가 담겨져  있는 녀석
	vTotalEffect m_vTotalEffect;

public:
	effectManager();
	~effectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addEffect(string effectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer);

	void play(string  effectKey, int x, int y);
};

