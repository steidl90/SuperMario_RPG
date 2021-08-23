#pragma once
//=======================================
//singletonBase(�̳༮���� �̱����� �����.)
//=======================================
/*
	�̱��� ������ static member�� �ϳ��� �ν��Ͻ���
	�����ȴ�. ���α׷� �ȿ��� ���������� ������ �����ϴ�.

	���������� �����ص� �ϳ��� �ν��Ͻ��� �����Ҽ� �ֱ� ������
	�̱��������� ����ϸ� Ŭ���� �ڽ��� �ڱ��� ������ �ν��Ͻ���
	�����ϴ� ����� ĸ��ȭ �Ͽ� ���� �Ҽ� �ִ�.
	���� ���, ��ü���� �� �Ҹ�, �ν��Ͻ� ���� ���� ����..
	Ȱ�뿡 �����ϴ�.

	�ڱ� �����ΰ� �ڱ��� ������ �ν��Ͻ��� �����ϴ�
	����� ��ü������ �����ϴ� ���� ����.
	�̳༮�� �ٸ� �ν��Ͻ��� �������� �ʵ��� ó���Ҽ� �ְ�
	���� ��� ���� ������ �Ѽ� �ִ�.
*/
template <typename T>
class Singleton
{
protected:
	//�̱��� �ν��Ͻ� �����ϱ�
	static T* singleton;

	Singleton() {};
	~Singleton() {};

public:
	static T* getSingleton();
	void releaseSingleton();

};

//�̱��� �ν��Ͻ� ����
template <typename T>
T* Singleton<T>::singleton = nullptr;

//�̱��� ��ü�� ��������
template<typename T>
T* Singleton<T>::getSingleton()
{
	//�̱��� ��ü�� ������ ���� �����ڤ�.
	if (!singleton)singleton = new T;

	return singleton;
}
template<typename T>
void Singleton<T>::releaseSingleton()
{
	//�̱��� ������ ����
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}