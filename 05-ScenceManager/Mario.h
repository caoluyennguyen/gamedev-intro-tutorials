#pragma once
#include "GameObject.h"

#define MARIO_MAX_WALKING_SPEED		0.1f 
#define MARIO_MIN_WALKING_SPEED		0.0005f 
#define MARIO_ACCELERATION_WALK		0.0002f
#define MARIO_ACCELERATION_JUMP		0.0003f
#define MARIO_GRAVITY				0.0005f
#define MARIO_JUMP_SPEED_Y			0.15f
#define MARIO_JUMP_DEFLECT_SPEED	0.2f
#define MARIO_DIE_DEFLECT_SPEED		0.2f

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
#define MARIO_ANI_SMALL_HIT_RIGHT			17
#define MARIO_ANI_SMALL_HIT_LEFT			18

#define MARIO_ANI_BIG_STOP_RIGHT			19
#define MARIO_ANI_BIG_STOP_LEFT				20
#define MARIO_ANI_BIG_JUMP_UP_RIGHT			21
#define MARIO_ANI_BIG_JUMP_UP_LEFT			22
#define MARIO_ANI_BIG_JUMP_DOWN_RIGHT		23
#define MARIO_ANI_BIG_JUMP_DOWN_LEFT		24
#define MARIO_ANI_BIG_IDLE_HOLD_RIGHT		25
#define MARIO_ANI_BIG_IDLE_HOLD_LEFT		26
#define MARIO_ANI_BIG_WALK_HOLD_RIGHT		27
#define MARIO_ANI_BIG_WALK_HOLD_LEFT		28
#define MARIO_ANI_BIG_HIT_RIGHT				29
#define MARIO_ANI_BIG_HIT_LEFT				30
#define MARIO_ANI_BIG_SIT_RIGHT				31
#define MARIO_ANI_BIG_SIT_LEFT				32

#define MARIO_ANI_TAIL_IDLE_RIGHT			33
#define MARIO_ANI_TAIL_IDLE_LEFT			34
#define MARIO_ANI_TAIL_WALKING_RIGHT		35
#define MARIO_ANI_TAIL_WALKING_LEFT			36
#define MARIO_ANI_TAIL_STOP_RIGHT			37
#define MARIO_ANI_TAIL_STOP_LEFT			38
#define MARIO_ANI_TAIL_JUMP_UP_RIGHT		39
#define MARIO_ANI_TAIL_JUMP_UP_LEFT			40
#define MARIO_ANI_TAIL_JUMP_DOWN_RIGHT		41
#define MARIO_ANI_TAIL_JUMP_DOWN_LEFT		42
#define MARIO_ANI_TAIL_IDLE_HOLD_RIGHT		43
#define MARIO_ANI_TAIL_IDLE_HOLD_LEFT		44
#define MARIO_ANI_TAIL_WALK_HOLD_RIGHT		45
#define MARIO_ANI_TAIL_WALK_HOLD_LEFT		46
#define MARIO_ANI_TAIL_HIT_RIGHT			47
#define MARIO_ANI_TAIL_HIT_LEFT				48
#define MARIO_ANI_TAIL_SIT_RIGHT			49
#define MARIO_ANI_TAIL_SIT_LEFT				50

#define MARIO_ANI_FIRE_IDLE_RIGHT			51
#define MARIO_ANI_FIRE_IDLE_LEFT			52
#define MARIO_ANI_FIRE_WALKING_RIGHT		53
#define MARIO_ANI_FIRE_WALKING_LEFT			54
#define MARIO_ANI_FIRE_STOP_RIGHT			55
#define MARIO_ANI_FIRE_STOP_LEFT			56
#define MARIO_ANI_FIRE_JUMP_UP_RIGHT		57
#define MARIO_ANI_FIRE_JUMP_UP_LEFT			58
#define MARIO_ANI_FIRE_JUMP_DOWN_RIGHT		59
#define MARIO_ANI_FIRE_JUMP_DOWN_LEFT		60
#define MARIO_ANI_FIRE_IDLE_HOLD_RIGHT		61
#define MARIO_ANI_FIRE_IDLE_HOLD_LEFT		62
#define MARIO_ANI_FIRE_WALK_HOLD_RIGHT		63
#define MARIO_ANI_FIRE_WALK_HOLD_LEFT		64
#define MARIO_ANI_FIRE_HIT_RIGHT			65
#define MARIO_ANI_FIRE_HIT_LEFT				66
#define MARIO_ANI_FIRE_SIT_RIGHT			67
#define MARIO_ANI_FIRE_SIT_LEFT				68

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

#define MARIO_TAIL_BBOX_WIDTH  15
#define MARIO_TAIL_BBOX_HEIGHT 29

#define MARIO_SIT_BBOX_WIDTH  16
#define MARIO_SIT_BBOX_HEIGHT 18

#define MARIO_UNTOUCHABLE_TIME	5000
#define MARIO_HITTING_TIME		200


class CMario : public CGameObject
{
	int level;
	int untouchable;
	int hitting;
	DWORD untouchable_start;
	DWORD hitting_start;

	float start_x;			// initial position of Mario at scene
	float start_y; 

	bool isAbleToJump;
	bool isAbleToHoldObject;
	bool isHoldObject;
public: 
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartHitObject() { hitting = 1; hitting_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	bool IsAbleToJump() { return isAbleToJump; }
	void SetAbleToJump(bool x) { isAbleToJump = x; }
	void SetAbleToHoldObject(bool x) { isAbleToHoldObject = x; }
};