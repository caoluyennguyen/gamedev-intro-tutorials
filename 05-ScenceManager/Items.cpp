#include "Items.h"

CItems::CItems(int type)
{
	this->type = type;
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

	vy += dy;
}

void CItems::Render()
{
	int ani = ITEM_ANI_COIN;
	if (state == ITEM_TYPE_COIN) {
		ani = ITEM_ANI_COIN;
	}

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
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
