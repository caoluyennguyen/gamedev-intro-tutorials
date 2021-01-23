#pragma once
#include "Enemy.h"
#include "FireBall.h"

#pragma region define
#define VENUS_STATE_RED				100
#define VENUS_STATE_RED_SHOOT		200
#define VENUS_STATE_GREEN			300
#define VENUS_STATE_GREEN_SHOOT		400
#define VENUS_STATE_PIRANHA_IDLE	500
#define VENUS_STATE_PIRANHA_MOVE	600
#define VENUS_STATE_DIE				700

#define VENUS_ANI_RED_UP_LEFT				0
#define VENUS_ANI_RED_DOWN_LEFT				1
#define VENUS_ANI_RED_UP_RIGHT				2
#define VENUS_ANI_RED_DOWN_RIGHT			3
#define VENUS_ANI_RED_SHOOT_UP_LEFT			4
#define VENUS_ANI_RED_SHOOT_DOWN_LEFT		5
#define VENUS_ANI_RED_SHOOT_UP_RIGHT		6
#define VENUS_ANI_RED_SHOOT_DOWN_RIGHT		7
#define VENUS_ANI_GREEN_UP_LEFT				8
#define VENUS_ANI_GREEN_DOWN_LEFT			9
#define VENUS_ANI_GREEN_UP_RIGHT			10
#define VENUS_ANI_GREEN_DOWN_RIGHT			11
#define VENUS_ANI_GREEN_SHOOT_UP_LEFT		12
#define VENUS_ANI_GREEN_SHOOT_DOWN_LEFT		13
#define VENUS_ANI_GREEN_SHOOT_UP_RIGHT		14
#define VENUS_ANI_GREEN_SHOOT_DOWN_RIGHT	15
#define VENUS_ANI_PIRANHA					16
#define VENUS_ANI_DIE						17

#define VENUS_SHOOT_TIME	2000
#define VENUS_DIE_TIME		500

#define VENUS_MOVE_SPEED	0.01f

#define VENUS_BBOX_HEIGHT	32
#define VENUS_BBOX_WIDTH	16
#define PIRANHA_BBOX_HEIGHT	23
#define PIRANHA_BBOX_WIDTH	16
#pragma endregion

class CVenus : public CEnemy
{
	float start_x;			// initial position of Venus at scene
	float start_y;

	bool isUp;			// look at mario?
	int direction;		// move direction

	bool isMoving;		// is moving up and down
	bool isShooting;	// is shooting

	DWORD startShoot;
	DWORD startDisappear;

	FireBall* fireball;
public:
	CVenus(int state, float start_y = 0);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void StartShoot();
};

