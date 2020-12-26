#pragma once
#include "GameObject.h"
#include "Effect.h"

#define ITEM_TYPE_COIN			0
#define ITEM_TYPE_LEAF			1
#define ITEM_TYPE_RED_MUSROOM	2
#define ITEM_TYPE_GREEN_MUSROOM	3

#define ITEM_ANI_COIN			0
#define ITEM_ANI_LEAF_LEFT		1
#define ITEM_ANI_LEAF_RIGHT		2
#define ITEM_ANI_RED_MUSROOM	3
#define ITEM_ANI_GREEN_MUSROOM	4

#define ITEM_COIN_BBOX_WIDTH	10.0f
#define ITEM_COIN_BBOX_HEIGHT	16.0f
#define ITEM_COIN_GRAVITY		0.0005f
#define ITEM_LEAF_GRAVITY		0.0001f

#define ITEM_ANIM_SET_ID	6

class CItems : public CGameObject
{
	int type;
	int startY;
	int ani;

	CEffect* effect;
public:
	CItems(int type);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetStartY(int startY) { this->startY = startY; }
	void SetPosition(float x, float y);
};

