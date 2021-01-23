#pragma once
#include "GameObject.h"

#define MOVING_WOOD_WIDTH	48
#define MOVING_WOOD_HEIGHT	16

#define MOVING_WOOD_SPEED	0.025f
#define MOVING_WOOD_GRAVITY		0.0002f

class CMovingWood : public CGameObject
{
	bool fallDown;
public:
	CMovingWood();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();
	virtual void SetState(int state) {};

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom) {};

	void SetFallDown() { fallDown = true; }
};