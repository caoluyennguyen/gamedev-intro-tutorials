#pragma once
#include "GameObject.h"

#define MIN_Y	145
#define MAX_Y	161

class CArrow : public CGameObject
{
public:
	CArrow() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};
