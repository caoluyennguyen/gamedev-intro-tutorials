#include "Items.h"

CItems::CItems()
{
	SetState(ITEM_TYPE_COIN);
}

void CItems::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ITEM_COIN_BBOX_WIDTH;

	if (state == ITEM_TYPE_COIN)
		bottom = y + ITEM_COIN_BBOX_HEIGHT;
}

void CItems::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	vy += dy;

	if (vx < 0 && x < 382) {
		x = 382; vx = -vx;
	}

	if (vx > 0 && x > 620) {
		x = 620; vx = -vx;
	}
}

void CItems::Render()
{
	int ani = ITEM_ANI_COIN;
	if (state == ITEM_TYPE_COIN) {
		ani = ITEM_ANI_COIN;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CItems::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_TYPE_COIN:
		vx = 0;
		vy = 0;
		break;
	}
}
