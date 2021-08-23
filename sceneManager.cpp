#include "framework.h"
#include "sceneManager.h"
#include "gameNode.h"
sceneManager::sceneManager()
{
}

sceneManager::~sceneManager()
{
}

// ������� �ΰ����� �ʱ�ȭ
gameNode* sceneManager::_currentScene = nullptr;

HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	isceneList iter = _sceneList.begin();
	for (iter; iter != _sceneList.end();)
	{
		// ����
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _sceneList.erase(iter);
		}
		else
		{
			iter++;
		}
		_sceneList.clear();
	}
}

void sceneManager::update()
{
	if (_currentScene)
	{
		_currentScene->update();
	}
}

void sceneManager::render()
{
	if (_currentScene)_currentScene->render();
}

gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	if (!scene) return nullptr;

	// ���鶧�� Ű���� ��� ��
	_sceneList.insert(make_pair(sceneName, scene));

	return nullptr;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	// ã�Ƽ� �ٲ�

	isceneList find = _sceneList.find(sceneName);

	// ��ã���� E_FAIL
	if(find == _sceneList.end()) return E_FAIL;

	// �ٲٷ��� ���� ���� ���̶� ���Ƶ� FAIL
	if(find->second == _currentScene) return E_FAIL;

	// ������� �Դٸ� ������ ����, �� ���� �ʱ�ȭ �ϰ� ����
	if (SUCCEEDED(find->second->init()))
	{
		// Ȥ�� ������ ���� �ִٸ� ������
		if (_currentScene) _currentScene->release();

		_currentScene = find->second;
		return S_OK;
	}
}
