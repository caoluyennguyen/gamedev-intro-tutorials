#pragma once
#include "GameObject.h"

class CGrass : public CGameObject
{
public:
	CGrass() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

