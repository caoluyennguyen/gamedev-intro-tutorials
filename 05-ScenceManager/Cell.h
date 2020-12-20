#pragma once
#include "GameObject.h"
#include <vector>

class Cell
{
	vector<LPGAMEOBJECT> listObjects;
public:
	void Add(CGameObject* obj, int id) { listObjects.push_back(obj); }
	vector<LPGAMEOBJECT> GetListObjects() { return listObjects; }
	void Unload() { listObjects.clear(); }
};

typedef Cell* LPCELL;