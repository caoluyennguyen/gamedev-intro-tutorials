#pragma once

#include "Enemy.h"

#define KOOPAS_WALKING_SPEED 0.03f;

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 15

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_ROLLING 300
#define KOOPAS_STATE_DIE_NGUA 400
#define KOOPAS_STATE_ROLLING_NGUA 500
#define KOOPAS_STATE_FLY 600
#define KOOPAS_STATE_RED 700
#define KOOPAS_STATE_RED_FLY 800

#define KOOPAS_ANI_WALKING_LEFT 0
#define KOOPAS_ANI_WALKING_RIGHT 1
#define KOOPAS_ANI_DIE 2
#define KOOPAS_ANI_DIE_NGUA 3
#define KOOPAS_ANI_ROLLING 4
#define KOOPAS_ANI_ROLLING_NGUA 5
#define KOOPAS_ANI_FLY_LEFT 6
#define KOOPAS_ANI_FLY_RIGHT 7
#define KOOPAS_RED_ANI_WALKING_LEFT 8
#define KOOPAS_RED_ANI_WALKING_RIGHT 9
#define KOOPAS_RED_ANI_DIE 10
#define KOOPAS_RED_ANI_DIE_NGUA 11
#define KOOPAS_RED_ANI_ROLLING 12
#define KOOPAS_RED_ANI_ROLLING_NGUA 13
#define KOOPAS_RED_ANI_FLY_LEFT 14
#define KOOPAS_RED_ANI_FLY_RIGHT 15

#define KOOPAS_GRAVITY 0.0005f
#define KOOPAS_GRAVITY_RED_FLY 0.0001f
#define KOOPAS_FLY_MAX_VY 0.1f

class CKoopas : public CEnemy
{
	DWORD jump;
	int color;
	int direction;
public:
	CKoopas(int state, int color = 0);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};