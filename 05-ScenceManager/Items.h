#pragma once
#include "GameObject.h"

#define ITEM_TYPE_COIN	0

#define ITEM_ANI_COIN	0

#define ITEM_COIN_BBOX_WIDTH	8.0f
#define ITEM_COIN_BBOX_HEIGHT	8.0f

class CItems : public CGameObject
{
public:
	CItems();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

