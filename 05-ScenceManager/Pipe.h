#pragma once
#include "GameObject.h"

#define PIPE_STATE_NORMAL				0
#define PIPE_STATE_SECRET_GREEN_DOWN	1
#define PIPE_STATE_SECRET_GREEN_UP		2
#define PIPE_STATE_SECRET_BLACK_DOWN	3
#define PIPE_STATE_SECRET_BLACK_UP		4

#define PIPE_WIDTH	32
#define PIPE_HEIGHT	49
#define PIPE_BLACK_HEIGHT	32

class CPipe : public CGameObject
{
public:
	float posMoveX, posMoveY;

	CPipe() {};
	CPipe(float posMoveX, float posMoveY) { this->posMoveX = posMoveX; this->posMoveY = posMoveY; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void Render();
	virtual void SetState(int state) { this->state = state; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
