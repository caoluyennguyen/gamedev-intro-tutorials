#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_AVAILABLE 0
#define BRICK_STATE_UNAVAILABLE 1

#define BRICK_ANI_AVAILABLE 0
#define BRICK_ANI_UNAVAILABLE 1

#define BRICK_GRAVITY 0.001f

class CBrick : public CGameObject
{
	int initialPosY;
	bool freeze;
public:
	CBrick(int initialPosY);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void SetState(int state);
};