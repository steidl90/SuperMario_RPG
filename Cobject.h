#pragma once
#include "gameNode.h"

class Cobject :public gameNode
{
private:

	/*
	Ÿ�� Ŭ������ ���� Ŭ�������� �������� �ʿ��� �κ��� ���⿡ ������
	Ÿ�� Ŭ������ ���� Ŭ�������� �������� �ʿ��� �κ��� ���⿡ ������
	Ÿ�� Ŭ������ ���� Ŭ�������� �������� �ʿ��� �κ��� ���⿡ ������
	*/

	// �ӽ� �÷��̾� ����

public:
	Cobject();
	~Cobject();

	HRESULT init();
	void release();
	void update();
	void render();

	//============== get ==============//

	
	//============== set ==============//


};

