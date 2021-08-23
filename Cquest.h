#pragma once
#include "CNPC.h"
class Cplayer;
class Cquest : public CNPC
{
private:
	CNPC* m_npc;
	Cplayer* m_player;

	image* m_questImage;
	image* m_findQuestImage;
	image* m_dialogImage;
	image* m_dialogBGImage;
	image* m_buttonImage;

	animation* m_questAni;

	RECT m_questRc;
	RECT m_dialogRc;
	RECT m_buttonRc;

	int m_x[3], m_y[3];
	int m_quest, m_maxQuest;
	bool m_isDialog;
	bool m_isQuesting;
	bool m_isComplete;
	bool m_isOneTime;

public:
	Cquest();
	~Cquest();

	HRESULT init();
	void release();
	void update();
	void render();

	bool collision();
	void dialog();
	void selectQuest();
	void stateQuest();

	void setQuest(int quest) { m_quest = quest; }
	int getQuest() { return m_quest; }

	void setMaxQuest(int maxQuest) { m_maxQuest = maxQuest; }
	int getMaxQuest() { return m_maxQuest; }

	void setIsDialog(bool dialog) { m_isDialog = dialog; }
	bool getIsDialog() { return m_isDialog; }

	void setIsQuesting(bool quest) { m_isQuesting = quest; }
	bool getIsQuesting() { return m_isQuesting; }
	
	void setIsComplete(bool complete) { m_isComplete = complete; }
	bool getIsComplete() { return m_isComplete; }

	void setPlayer(Cplayer* player) { m_player = player; }
	void setNPC(CNPC* NPC) { m_npc = NPC; }
	
};

