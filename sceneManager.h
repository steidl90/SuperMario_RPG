#pragma once
#include"singleton.h"

class gameNode;
class sceneManager : public Singleton<sceneManager>
{

private:

	// 키값과 노드
	typedef map<string, gameNode*> sceneList;
	typedef map<string, gameNode*>::iterator isceneList;

	static gameNode* _currentScene;
	sceneList _sceneList;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	gameNode* addScene(string sceneName, gameNode* scene);
	HRESULT changeScene(string sceneName);
};

