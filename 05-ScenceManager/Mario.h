#pragma once
#include "GameObject.h"
#include "FireBall.h"
#include "Tail.h"

#pragma region define
#define MARIO_MAX_WALKING_SPEED			0.1f 
#define MARIO_DIVING_SPEED				0.05f 
#define MARIO_MAX_RUN_SPEED				0.2f 
#define MARIO_MIN_WALKING_SPEED			0.0005f 
#define MARIO_ACCELERATION_WALK			0.0002f
#define MARIO_ACCELERATION_RUN			0.0004f
#define MARIO_ACCELERATION_JUMP			0.0003f
#define MARIO_ACCELERATION_JUMP_HIGH	0.0004f
#define MARIO_GRAVITY					0.0005f
#define MARIO_GRAVITY_SLOW_FALL			0.0001f
#define MARIO_JUMP_SPEED				0.18f
#define MARIO_JUMP_HIGH_SPEED			0.2f
#define MARIO_JUMP_DEFLECT_SPEED		0.2f
#define MARIO_DIE_DEFLECT_SPEED			0.2f
#define MARIO_MIN_JUMP_SPEED			0.1f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_SIT				500
#define MARIO_STATE_RUN_RIGHT		600
#define MARIO_STATE_RUN_LEFT		700
#define MARIO_STATE_JUMP_HIGH		800
#define MARIO_STATE_HIT				900
#define MARIO_STATE_FLY				1000
#define MARIO_STATE_SLOW_FALL		1100
#define MARIO_STATE_GO_DOWN_PIPE	1200
#define MARIO_STATE_GO_UP_PIPE		1300

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
#define MARIO_ANI_SMALL_RUN_RIGHT			69
#define MARIO_ANI_SMALL_RUN_LEFT			70
#define MARIO_ANI_SMALL_SWIFT_RIGHT			71
#define MARIO_ANI_SMALL_SWIFT_LEFT			72
#define MARIO_ANI_SMALL_FLY_RIGHT			73
#define MARIO_ANI_SMALL_FLY_LEFT			74

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
#define MARIO_ANI_BIG_RUN_RIGHT				75
#define MARIO_ANI_BIG_RUN_LEFT				76
#define MARIO_ANI_BIG_SWIFT_RIGHT			77
#define MARIO_ANI_BIG_SWIFT_LEFT			78
#define MARIO_ANI_BIG_FLY_RIGHT				79
#define MARIO_ANI_BIG_FLY_LEFT				80

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
#define MARIO_ANI_TAIL_RUN_RIGHT			81
#define MARIO_ANI_TAIL_RUN_LEFT				82
#define MARIO_ANI_TAIL_SWIFT_RIGHT			83
#define MARIO_ANI_TAIL_SWIFT_LEFT			84
#define MARIO_ANI_TAIL_JUMP_HIGH_RIGHT		85
#define MARIO_ANI_TAIL_JUMP_HIGH_LEFT		86
#define MARIO_ANI_TAIL_FLY_RIGHT			87
#define MARIO_ANI_TAIL_FLY_LEFT				88
#define MARIO_ANI_TAIL_HIT_TAIL_RIGHT		89
#define MARIO_ANI_TAIL_HIT_TAIL_LEFT		90
#define MARIO_ANI_TAIL_SLOW_FALL_RIGHT		103
#define MARIO_ANI_TAIL_SLOW_FALL_LEFT		104

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
#define MARIO_ANI_FIRE_RUN_RIGHT			91
#define MARIO_ANI_FIRE_RUN_LEFT				92
#define MARIO_ANI_FIRE_SWIFT_RIGHT			93
#define MARIO_ANI_FIRE_SWIFT_LEFT			94
#define MARIO_ANI_FIRE_FLY_RIGHT			97
#define MARIO_ANI_FIRE_FLY_LEFT				98
#define MARIO_ANI_FIRE_THROW_BALL_RIGHT		99
#define MARIO_ANI_FIRE_THROW_BALL_LEFT		100
#define MARIO_ANI_FIRE_JUMP_HIT_RIGHT		101
#define MARIO_ANI_FIRE_JUMP_HIT_LEFT		102
#define MARIO_ANI_SMALL_TRANSFORM_RIGHT		105
#define MARIO_ANI_BIG_TRANSFORM				106
#define MARIO_ANI_SMALL_TRANSFORM_LEFT		107

#define MARIO_ANI_SMALL_GO_DOWN_PIPE		108
#define MARIO_ANI_SMALL_GO_UP_PIPE			109
#define MARIO_ANI_BIG_GO_DOWN_PIPE			110
#define MARIO_ANI_BIG_GO_UP_PIPE			111

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_TAIL	3
#define	MARIO_LEVEL_FIRE	4

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 16

#define MARIO_SIT_BBOX_WIDTH  16
#define MARIO_SIT_BBOX_HEIGHT 18

#define MARIO_UNTOUCHABLE_TIME	5000
#define MARIO_HITTING_TIME		500
#define MARIO_SHOOTING_TIME		200
#define MARIO_THROWING_TIME		200
#define MARIO_FLYING_TIME		4000
#define MARIO_TRANSFORM_TIME	500

#define MARIO_MAX_POSITION	2528
#pragma endregion

class CMario : public CGameObject
{
	float a;
	int level;
	int untouchable;
	int hitting;
	bool flying;
	int shooting;
	int throwing;
	int countBall;
	int ani;
	DWORD untouchable_start;
	DWORD hitting_start;
	DWORD flying_start;
	DWORD minimize_start;
	DWORD shooting_start;
	DWORD throwing_start;
	DWORD transform_start;
	DWORD coin_start;
	DWORD go_into_pipe_start;

	float start_x;			// initial position of Mario at scene
	float start_y; 

	bool isAbleToJump;			// check if mario can jump
	bool isAbleToHoldObject;	// check if mario can hold object
	bool isHoldObject;			// check if mario is holding object
	bool isAbleToRun;			// check if mario can run
	bool isAbleToJumpHigh;		// check if mario can jump high
	bool isAbleToShoot;			// check if mario can shoot
	bool isAbleToSlowFall;		// check if mario can fall slowloy
	bool isAbleToFly;			// check if mario can fly
	//bool isJumping;				// check if mario is in the air
	bool isSlowFall;
	bool isTransform;
	bool isAbleToGoDownPipe;
	bool isAbleToGoUpPipe;
	bool isGoingIntoPipe;
	bool moveEndScene;
	bool moveCamera;
	bool isWalking;
	bool isOnWood;

	vector<FireBall*> fireBalls;
	FireBall* fireball;
	Tail* tail;

	static CMario* __instance;
public: 
	
	CMario();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);

	void SetState(int state);
	void SetLevel(int l);
	int GetLevel() { return level; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartShootingObject() { shooting = 1; shooting_start = GetTickCount(); }
	void StartHittingObject() { hitting = 1; hitting_start = GetTickCount();}
	void StartThrowingObject() { throwing = 1; throwing_start = GetTickCount(); StartShoot(); }
	void StartFly() { flying = true; flying_start = GetTickCount(); }
	void StartTransform() { isTransform = true; transform_start = GetTickCount(); }
	void StartTransformCoin() { coin_start = GetTickCount(); }
	void StartGoIntoPipe() { go_into_pipe_start = GetTickCount(); isGoingIntoPipe = true; }

	void Reset();
	void Clear();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	bool IsAbleToJump() { return isAbleToJump; }
	bool IsAbleToJumpHigh() { return isAbleToJumpHigh; }
	bool IsAbleToRun() { return isAbleToRun; }
	bool IsAbleToShoot() { return isAbleToShoot; }
	bool IsAbleToSlowFall() { return isAbleToSlowFall; }
	bool IsAbleToGoDownPipe() { return isAbleToGoDownPipe; }
	bool IsAbleToGoUpPipe() { return isAbleToGoUpPipe; }
	bool IsFlying() { return flying; }
	bool IsMoveEndScene() { return moveEndScene; }
	void SetAbleToJump(bool x) { isAbleToJump = x; }
	void SetAbleToHoldObject(bool x) { isAbleToHoldObject = x; }
	void SetAbleToRun(bool x) { isAbleToRun = x; }
	void SetAbleToJumpHigh(bool x) { isAbleToJumpHigh = x; }
	void SetIsSlowFall(bool x) { isSlowFall = x; }
	void StartShoot();
	//void SetIsJumping(bool x) { isJumping = x; }
	void SetNx(int nx) { this->nx = nx; }
	void ResetBall() { countBall++ ; }
	void SetMoveCamera(bool move) { this->moveCamera = move; }
	void SetIsWalking(bool walking) { this->isWalking = walking; }
	void SetIsOnWood(bool onWood) { this->isOnWood = onWood; }

	static CMario* CMario::GetInstance();
};