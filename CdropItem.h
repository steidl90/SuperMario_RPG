#pragma once
#include "Cobject.h"
class Citem;
class CdropItem : public Cobject
{
private:

	vector<Citem*> m_vDropItemList;
	vector<DropItem> m_vDropItem;
	vector<DropItem>::iterator m_viDropItem;
	int m_count;

public:


	HRESULT init();
	void release();
	void update();
	void render();


	Citem* getItem();
	void makeItem(float x, float y);
	void makeFinalItem(float x, float y);
	void removeItem(int num);

	vector<DropItem> getDropItemList() { return m_vDropItem; }
};

