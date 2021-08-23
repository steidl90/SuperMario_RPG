#pragma once
#include"singleton.h"
#include<bitset>
using namespace std;
#define KEYMAX 256
class Input : public Singleton<Input>
{
private:

	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	Input();
	~Input();

	HRESULT init();

	void release();

	//�ѹ��� ������
	bool isOnceKeyDown(int key);
	//�����ٰ� �³�
	bool isOnceKeyUp(int key);
	//������ �ֳ�
	bool isStayKeyDown(int key);
	//���Ű��
	bool isToggleKey(int key);
};
