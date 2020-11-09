#pragma once
#include "GameObject.h"

#define ITEM_TYPE_COIN	0

#define ITEM_ANI_COIN	0

#define ITEM_COIN_BBOX_WIDTH	10.0f
#define ITEM_COIN_BBOX_HEIGHT	16.0f

#define ITEM_ANIM_SET_ID	6

class CItems : public CGameObject
{
	int type;
	int startY;
public:
	CItems(int type);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

