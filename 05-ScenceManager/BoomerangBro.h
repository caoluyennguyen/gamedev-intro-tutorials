#pragma once
#include "Enemy.h"
#include "Boomerang.h"

#define BOOMERANG_BRO_STATE_WALKING	0
#define BOOMERANG_BRO_STATE_SHOOTING 1
#define BOOMERANG_BRO_STATE_DIE		2

#define BOOMERANG_BRO_ANI_WALKING_RIGHT		0
#define BOOMERANG_BRO_ANI_SHOOTING_RIGHT	1
#define BOOMERANG_BRO_ANI_DIE				2
#define BOOMERANG_BRO_ANI_WALKING_LEFT		4
#define BOOMERANG_BRO_ANI_SHOOTING_LEFT		5

#define BOOMERANG_BRO_STATE_GRAVITY		0.0002f
#define BOOMERANG_BRO_STATE_VELOCITY	0.02f

#define BOOMERANG_BRO_TIME_MOVE		2000
#define BOOMERANG_BRO_TIME_FIRST_SHOOT	4000
#define BOOMERANG_BRO_TIME_SECOND_SHOOT	4000

#define BOOMERANG_BRO_BBOX_WIDTH	16.0f
#define BOOMERANG_BRO_BBOX_HEIGHT	15.0f

class CBoomerangBro : public CEnemy
{
	DWORD changeDirection;
	DWORD startShoot;
	bool fShooting;
	bool sShooting;
	int direction;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CBoomerang* fBoomerang;
	CBoomerang* sBoomerang;

	CBoomerangBro();
	virtual void SetState(int state);
	void StartChange() { changeDirection = GetTickCount(); }

	void SetDirection(int direction) { this->direction = direction; }
};