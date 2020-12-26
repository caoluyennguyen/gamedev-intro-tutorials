#pragma once
#include "GameObject.h"

#define PIPE_STATE_NORMAL	0
#define PIPE_STATE_SECRET	1

#define PIPE_WIDTH	32
#define PIPE_HEIGHT	49

class CPipe : public CGameObject
{
public:
	CPipe() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void Render();
	virtual void SetState(int state) { this->state = state; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
