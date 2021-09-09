#pragma once
#include"singleton.h"

class gameNode;
class sceneManager : public Singleton<sceneManager>
{

private:

	// Ű���� ���
	typedef map<string, gameNode*> sceneList;
	typedef map<string, gameNode*>::iterator isceneList;

	static gameNode* _currentScene;
	sceneList _sceneList;

	isceneList find;
public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	gameNode* addScene(string sceneName, gameNode* scene);
	HRESULT changeScene(string sceneName);
	HRESULT changeFieldScene(string sceneName, int num);
	HRESULT changeBattleScene(string sceneName);

	gameNode* Find(string findDate);

	
};