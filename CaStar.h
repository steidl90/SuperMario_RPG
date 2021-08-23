#pragma once
#include "gameNode.h"

#define TILE_X 50
#define TILE_Y 50
#define WIDTH  36
#define HEIGHT 36
#define BIGNUM 5000

enum class TILE_TYPE
{
	TILE_TYPE_EMPTY,
	TILE_TYPE_START,
	TILE_TYPE_END,
	TILE_TYPE_WALL
};

enum class ASTAR_STATE
{
	ASTAR_STATE_SEARCHING,
	ASTAR_STATE_FOUND,
	ASTAR_STATE_NOWAY,
	ASTAR_STATE_END
};
struct aStarTile
{
	RECT rc;
	COLORREF color;
	bool walkable;		
	bool listOn;		
	int i, j;
	int F, G, H;
	char str[128];

	aStarTile* parent;
	TILE_TYPE type;
};

class Cplayer;
class camera;
class CaStar :public gameNode
{

private:
	//camera* m_camera;
	//Cplayer* m_player;
private:
	aStarTile _tile[TILE_X][TILE_Y];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;
	// 추가
	vector<POINT> m_fastLoad;
	list<POINT> m_fastLoadLocation;

	POINT m_targetIndex;
	POINT m_currentTarget;

	POINT m_startIndex;

	ASTAR_STATE _astarState;
	TILE_TYPE _selectType;
	COLORREF _selectedTypeColor;

	ATTRIBUTE* m_attribute;

	int _startX, _startY;
	int _endX, _endY;
	int _lastIndex;

	bool _startPointSet;
	bool _endPointSet;

	bool isButtonClick;
	bool isKeyUp;

	int Ci;
	int Cj;
	int Cg;

	RECT rc[6];
	HBRUSH newBrush, oldBrush;
	HFONT newFont, oldFont;

public:
	CaStar();
	~CaStar();

	HRESULT init();
	HRESULT init2();
	void release();
	void update();
	void render();

	void tileComposition();	
	void tileInitializing();
	void addOpenList();		
	void caculateH();		
	void caculateF();		
	void addCloseList();	
	void checkArrive();		
	void showWay(aStarTile* tile);
	void typeColor(TILE_TYPE type);

	// 추가
	void setTargetIndex(POINT index) { m_targetIndex = index; }
	void setStartIndex(POINT index) { m_startIndex = index; }
	//void setPlayer(Cplayer* player) { m_player = player; }
	vector<POINT>* getFastLoad() { return &m_fastLoad; }
	list<POINT>* getFastLoadLocation() { return &m_fastLoadLocation; }
	//void setCameraMemory(camera* cm) { m_camera = cm; }
	void setAttribute(ATTRIBUTE* att) { m_attribute = att; }
};


