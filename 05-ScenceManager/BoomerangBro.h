#pragma once
#include "Enemy.h"
#include "Boomerang.h"

#define BOOMERANG_BRO_STATE_WALKING	0
#define BOOMERANG_BRO_STATE_SHOOTING 1
#define BOOMERANG_BRO_STATE_DIE		2

#define BOOMERANG_BRO_STATE_GRAVITY		0.0002f

#define BOOMERANG_BRO_BBOX_WIDTH	16.0f
#define BOOMERANG_BRO_BBOX_HEIGHT	15.0f

class CBoomerangBro : public CEnemy
{
	CBoomerang* boomerang;
	DWORD changeDirection;
	bool isAbleToJump;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CBoomerangBro();
	virtual void SetState(int state);
	void StartChange() { changeDirection = GetTickCount(); }
};