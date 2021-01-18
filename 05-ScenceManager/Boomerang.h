#pragma once
#include "GameObject.h"

#define BOOMERANG_ANIM_SET_ID	3

#define BOOMERANG_BBOX_WIDTH	16
#define BOOMERANG_BBOX_HEIGHT	16

class CBoomerang : public CGameObject
{
public:
	CBoomerang();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	float GetPositionX() { return this->x; };
};

