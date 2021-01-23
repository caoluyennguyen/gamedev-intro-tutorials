#pragma once
#include "GameObject.h"

#define STAGE_VELOCITY	0.6f
#define SCROLL_STAGE_MIN_Y	200.0f

class CScrollStage : public CGameObject
{
public:
	CScrollStage() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};