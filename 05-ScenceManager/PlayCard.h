#pragma once
#include "GameObject.h"

#define CARD_STATE_NORMAL	0
#define CARD_STATE_STAR		1
#define CARD_STATE_FLOWER	2
#define CARD_STATE_MUSROOM	3

#define CARD_ANIM_SET_ID	12

class CPlayCard : public CGameObject
{
public:
	CPlayCard();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};

	float GetPositionX() { return this->x; };
};

