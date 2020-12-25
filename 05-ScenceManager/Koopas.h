#pragma once

#include "Enemy.h"

#define KOOPAS_WALKING_SPEED 0.03f;

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_ROLLING 300
#define KOOPAS_STATE_DIE_NGUA 400
#define KOOPAS_STATE_ROLLING_NGUA 500
#define KOOPAS_STATE_FLY 600

#define KOOPAS_ANI_WALKING_LEFT 0
#define KOOPAS_ANI_WALKING_RIGHT 1
#define KOOPAS_ANI_DIE 2
#define KOOPAS_ANI_DIE_NGUA 3
#define KOOPAS_ANI_ROLLING 4
#define KOOPAS_ANI_ROLLING_NGUA 5
#define KOOPAS_ANI_FLY_LEFT 6
#define KOOPAS_ANI_FLY_RIGHT 7

#define KOOPAS_GRAVITY 0.0005f

class CKoopas : public CEnemy
{
	DWORD jump;
public:
	CKoopas(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};