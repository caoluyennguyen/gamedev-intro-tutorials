#pragma once
#include "GameObject.h"
#include "Items.h"
#include "BrickPiece.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_AVAILABLE 0
#define BRICK_STATE_UNAVAILABLE 1
#define BRICK_STATE_BREAKABLE 2
#define BRICK_STATE_BREAK 3
#define BRICK_STATE_COIN 4
#define BRICK_STATE_MULTI_COIN 5
#define BRICK_STATE_MULTI_COIN_AVAILABLE 6

#define BRICK_ANI_AVAILABLE 0
#define BRICK_ANI_UNAVAILABLE 1
#define BRICK_ANI_BREAKABLE 2
#define BRICK_ANI_COIN 4

#define BRICK_GRAVITY 0.001f
#define BRICK_COIN_TIME 5000

class CBrick : public CGameObject
{
	int initialPosX;
	int initialPosY;
	bool breakable;

	CItems* item;
	BrickPieces* pieces;

	DWORD coin_start;
public:
	int count;
	bool freeze;
	CBrick(int initialPosX, int initialPosY, int itemType = 0);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	CItems* GetItem() { return item; }
	void SetState(int state);
	void InitItem(int itemType);
	void InitPieces();

};