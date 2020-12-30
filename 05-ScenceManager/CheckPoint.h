#pragma once
#include "Animations.h"
#include "GameObject.h"

#define CHECKPOINT_BBOX_WIDTH	16
#define CHECKPOINT_BBOX_HEIGHT	16

class CCheckPoint : public CGameObject
{
public:
	int left, right, bottom, top;

	CCheckPoint() {};
	CCheckPoint(int left = 0, int top = 0, int right = 1, int bottom = 0);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
