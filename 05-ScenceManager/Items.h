#pragma once
#include "GameObject.h"
#include "Effect.h"

#pragma region define
#define ITEM_TYPE_COIN			0
#define ITEM_TYPE_LEAF			1
#define ITEM_TYPE_RED_MUSROOM	2
#define ITEM_TYPE_GREEN_MUSROOM	3
#define ITEM_TYPE_SWITCH_BLOCK_UP	4
#define ITEM_TYPE_SWITCH_BLOCK_DOWN	5

#define ITEM_ANI_COIN			0
#define ITEM_ANI_LEAF_LEFT		1
#define ITEM_ANI_LEAF_RIGHT		2
#define ITEM_ANI_RED_MUSROOM	3
#define ITEM_ANI_GREEN_MUSROOM	4
#define ITEM_ANI_SWITCH_BLOCK_UP	5
#define ITEM_ANI_SWITCH_BLOCK_DOWN	6

#define ITEM_COIN_GRAVITY		0.0005f
#define ITEM_COIN_VELOCITY		0.2f
#define ITEM_LEAF_GRAVITY		0.0001f
#define ITEM_LEAF_VELOCITY_X	0.0005f
#define ITEM_LEAF_VELOCITY_Y	0.1f
#define ITEM_LEAF_MAX_VELOCITY	0.1f
#define ITEM_MUSROOM_GRAVITY	0.0001f
#define ITEM_MUSROOM_VELOCITY_X	0.05f
#define ITEM_MUSROOM_VELOCITY_Y	-0.01f

#define ITEM_COIN_BBOX_WIDTH		10.0f
#define ITEM_COIN_BBOX_HEIGHT		16.0f
#define ITEM_LEAF_BBOX_WIDTH		16.0f
#define ITEM_LEAF_BBOX_HEIGHT		14.0f
#define ITEM_MUSROOM_BBOX_WIDTH		16.0f
#define ITEM_MUSROOM_BBOX_HEIGHT	16.0f
#define ITEM_SWITCH_BBOX_HEIGHT		7.0f

#define ITEM_ANIM_SET_ID	6

#define ITEM_INITIAL_POS_X	3.0f
#define ITEM_INITIAL_POS_Y	16.0f
#define MUSROOM_LIMIT_POS_Y		3.0f
#define MUSROOM_INITIAL_POS_Y	9.0f
#pragma endregion

class CItems : public CGameObject
{
	float startY;
	int ani;

	bool appear;

public:
	CEffect* effect;
	CItems(int type);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetStartY(float startY) { this->startY = startY; }
	void SetPosition(float x, float y);

	void CoinUpdate(DWORD dt);
	void LeafUpdate(DWORD dt);
	void MusroomUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SwitchBlockUpdate(DWORD dt);
};

