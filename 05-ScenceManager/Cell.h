#pragma once
#include "GameObject.h"
#include <vector>

class Cell
{
	vector<int> listObjectId;
	vector<CGameObject*> listObjects;
public:
	void Add(CGameObject* obj, int id) { listObjects.push_back(obj); listObjectId.push_back(id); }
	vector<CGameObject*> GetListObjects() { return listObjects; }
	void Unload() { listObjects.clear(); }
};

typedef Cell* LPCELL;