#include "framework.h"
#include "sceneManager.h"
#include "gameNode.h"
sceneManager::sceneManager()
{
}

sceneManager::~sceneManager()
{
}

// 현재씬을 널값으로 초기화
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
		// 삭제
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

	// 만들때는 키값과 밸류 쌍
	_sceneList.insert(make_pair(sceneName, scene));

	return nullptr;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	// 찾아서 바꿈

	isceneList find = _sceneList.find(sceneName);

	// 못찾으면 E_FAIL
	if(find == _sceneList.end()) return E_FAIL;

	// 바꾸려는 씬이 현재 씬이랑 같아도 FAIL
	if(find->second == _currentScene) return E_FAIL;

	// 여기까지 왔다면 문제가 없다, 즉 씬을 초기화 하고 변경
	if (SUCCEEDED(find->second->init()))
	{
		// 혹시 기존의 씬이 있다면 릴리즈
		if (_currentScene) _currentScene->release();

		_currentScene = find->second;
		return S_OK;
	}
}

HRESULT sceneManager::changeFieldScene(string sceneName, int num)
{
	// 찾아서 바꿈

	isceneList find = _sceneList.find(sceneName);

	// 못찾으면 E_FAIL
	if (find == _sceneList.end()) return E_FAIL;

	// 바꾸려는 씬이 현재 씬이랑 같아도 FAIL
	if (find->second == _currentScene) return E_FAIL;

	// 여기까지 왔다면 문제가 없다, 즉 씬을 초기화 하고 변경
	if (SUCCEEDED(find->second->initBattle(num)))
	{
		// 혹시 기존의 씬이 있다면 릴리즈
		//if (_currentScene) _currentScene->release();

		_currentScene = find->second;
		return S_OK;
	}
}

HRESULT sceneManager::changeBattleScene(string sceneName)
{
	// 찾아서 바꿈

	isceneList find = _sceneList.find(sceneName);

	// 못찾으면 E_FAIL
	if (find == _sceneList.end()) return E_FAIL;

	// 바꾸려는 씬이 현재 씬이랑 같아도 FAIL
	if (find->second == _currentScene) return E_FAIL;

	// 여기까지 왔다면 문제가 없다, 즉 씬을 초기화 하고 변경
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}
}

gameNode* sceneManager::Find(string findDate)
{
	isceneList find = _sceneList.find(findDate);
	return find->second;
}