#pragma once
#include "GameObject.h"

#define MARIO_BBOX_WIDTH	16
#define MARIO_BBOX_HEIGHT	16

#define MARIO_VELOCITY	0.07f

class CArrow : public CGameObject
{
	bool isMoving;
public:
	CArrow();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};
