#pragma once
#include "GameObject.h"

#define FIREBALL_BBOX_WIDTH		8
#define FIREBALL_BBOX_HEIGHT	8
#define FIREBALL_VELOCITY_X		0.1f
#define FIREBALL_VELOCITY_Y		-0.2f
#define FIREBALL_GRAVITY		0.001f
#define FIREBALL_ANIM_SET_ID	5

#define FIREBALL_STATE_NORMAL	0
#define FIREBALL_STATE_VENUS	1

class FireBall : public CGameObject
{
public:
	FireBall();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	float GetPositionX() { return this->x; };
};

