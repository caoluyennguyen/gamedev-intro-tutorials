#pragma once
#include "GameObject.h"

#define BOOMERANG_ANIM_SET_ID	3

#define BOOMERANG_BBOX_WIDTH	16
#define BOOMERANG_BBOX_HEIGHT	16

#define BOOMERANG_TIME_X	1000
#define BOOMERANG_VELOCITY	0.1f

class CBoomerang : public CGameObject
{
	DWORD fly_x;
public:
	CBoomerang();
	virtual void Update(DWORD dt);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	float GetPositionX() { return this->x; };
	void Reset() { fly_x = GetTickCount(); vx = BOOMERANG_VELOCITY; enable = false; }
};

