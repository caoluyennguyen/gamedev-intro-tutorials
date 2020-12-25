#pragma once
#include "Enemy.h"

#define GOOMBA_WALKING_SPEED 0.05f;

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_DIE_NGUA 300
#define GOOMBA_STATE_FLY 400

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1
#define GOOMBA_ANI_DIE_NGUA 2
#define GOOMBA_ANI_FLY 3

#define GOOMBA_GRAVITY 0.0005f
#define TIME_APPEAR	1000
#define TIME_JUMP_HIGH	2000

class CGoomba : public CEnemy
{
	DWORD disappear;
	DWORD jump;
	bool isAbleToJump;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

public: 	
	CGoomba(int state);
	virtual void SetState(int state);
	void StartDisappear() { disappear = GetTickCount(); }
	void StartJump() { jump = GetTickCount(); }
};