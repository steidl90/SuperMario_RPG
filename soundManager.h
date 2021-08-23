#pragma once
#include"singleton.h"
#include"inc/fmod.hpp"
#pragma comment(lib,"lib/fmodex_vc.lib")
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 100
#define TOTALSOUNDBUFFER SOUNDBUFFER+EXTRACHANNELBUFFER
class soundManager : public Singleton<soundManager>
{
private:

	typedef map<string, FMOD::Sound**> arrSounds;
	typedef map<string, FMOD::Sound**>::iterator arrSoundIter;


	FMOD::System* m_system;

	FMOD::Sound** m_sound;
	FMOD::Channel** m_channel;

	arrSounds m_totalSounds;

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// 첫번째 키값, 두번째 파일이름, 세번째는 백그라운드, 네번째는 반복여부
	void addSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);

	// 볼륨 범위는 0.0 ~ 1.0
	void play(string keyName, float volume = 1.0f);

	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	// 플레이 중이냐
	bool isPlaySound(string keyName);
	// 일시정지 중이냐
	bool isPauseSound(string keyName);

};

