#pragma once
#include "GameObject.h"

#define BOOMERANG_ANIM_SET_ID	3

#define BOOMERANG_BBOX_WIDTH	16
#define BOOMERANG_BBOX_HEIGHT	16

#define BOOMERANG_TIME_X	1000
#define BOOMERANG_VELOCITY_X	0.1f
#define BOOMERANG_VELOCITY_Y	-0.1f
#define BOOMERANG_GRAVITY	0.0002f

class CBoomerang : public CGameObject
{
	DWORD fly_x;
	int direction;
	bool flyBack;
public:
	CBoomerang();
	virtual void Update(DWORD dt);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	float GetPositionX() { return this->x; };
	void StartFly() { fly_x = GetTickCount(); flyBack = false; }
	void Reset() { fly_x = GetTickCount(); vx = BOOMERANG_VELOCITY_X; vy = BOOMERANG_VELOCITY_Y; enable = false; }
	bool IsFlyBack() { return flyBack; }
	void SetFlyBack(bool fly) { flyBack = fly; }

	void SetDirection(int direction) { this->direction = direction; }
};

