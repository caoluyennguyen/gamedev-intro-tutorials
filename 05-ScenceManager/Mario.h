#pragma once
#include "GameObject.h"

#define MARIO_MAX_WALKING_SPEED		0.1f 
#define MARIO_MIN_WALKING_SPEED		0.0005f 
#define MARIO_ACCELERATION_WALK		0.0002f
#define MARIO_ACCELERATION_JUMP		0.0002f
#define MARIO_GRAVITY				0.0005f
#define MARIO_JUMP_SPEED_Y			0.2f
#define MARIO_JUMP_DEFLECT_SPEED	0.2f
#define MARIO_DIE_DEFLECT_SPEED		0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_SIT				500
#define MARIO_STATE_FLY				600

#define MARIO_ANI_BIG_IDLE_RIGHT			0
#define MARIO_ANI_BIG_IDLE_LEFT				1
#define MARIO_ANI_SMALL_IDLE_RIGHT			2
#define MARIO_ANI_SMALL_IDLE_LEFT			3

#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7

#define MARIO_ANI_DIE						8
#define MARIO_ANI_SMALL_STOP_RIGHT			9
#define MARIO_ANI_SMALL_STOP_LEFT			10
#define MARIO_ANI_SMALL_JUMP_RIGHT			11
#define MARIO_ANI_SMALL_JUMP_LEFT			12
#define MARIO_ANI_SMALL_IDLE_HOLD_RIGHT		13
#define MARIO_ANI_SMALL_IDLE_HOLD_LEFT		14
#define MARIO_ANI_SMALL_WALK_HOLD_RIGHT		15
#define MARIO_ANI_SMALL_WALK_HOLD_LEFT		16

//#define MARIO_ANI_BIG_JUMP_UP_RIGHT			9
//#define MARIO_ANI_BIG_JUMP_UP_LEFT			10
//#define MARIO_ANI_BIG_JUMP_DOWN_RIGHT		11
//#define MARIO_ANI_BIG_JUMP_DOWN_RIGHT		12

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_TAIL	3
#define	MARIO_LEVEL_FIRE	4

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000


class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y; 

	bool isAbleToJump;
	bool isHoldObject;
public: 
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	bool IsAbleToJump() { return isAbleToJump; }
	void SetAbleToJump(bool x) { isAbleToJump = x; }
};