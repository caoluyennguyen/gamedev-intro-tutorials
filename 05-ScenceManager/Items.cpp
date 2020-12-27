#include "Items.h"

CItems::CItems(int type)
{
	SetState(type);
	ani = ITEM_ANI_COIN;
	effect = new CEffect();
	nx = -1;
}

void CItems::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (state == ITEM_TYPE_COIN)
	{
		right = x + ITEM_COIN_BBOX_WIDTH;
		bottom = y + ITEM_COIN_BBOX_HEIGHT;
	}
	else if (state == ITEM_TYPE_LEAF)
	{
		right = x + ITEM_LEAF_BBOX_WIDTH;
		bottom = y + ITEM_LEAF_BBOX_HEIGHT;
	}
	else
	{
		right = x + ITEM_MUSROOM_BBOX_WIDTH;
		bottom = y + ITEM_MUSROOM_BBOX_HEIGHT;
	}
}

void CItems::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (enable)
	{
		if (state == ITEM_TYPE_COIN) CoinUpdate(dt);
		else if (state == ITEM_TYPE_LEAF) LeafUpdate(dt, coObjects);
	}

	effect->Update(dt);
}

void CItems::Render()
{
	if (enable)
	{
		if (state == ITEM_TYPE_COIN) {
			ani = ITEM_ANI_COIN;
		}
		else if (state == ITEM_TYPE_LEAF) {
			if (vx > 0) ani = ITEM_ANI_LEAF_RIGHT;
			else ani = ITEM_ANI_LEAF_LEFT;
		}
		else if (state == ITEM_TYPE_RED_MUSROOM) {
			ani = ITEM_ANI_RED_MUSROOM;
		}
		else if (state == ITEM_TYPE_GREEN_MUSROOM) {
			ani = ITEM_ANI_GREEN_MUSROOM;
		}

		animation_set->at(ani)->Render(x, y);

		RenderBoundingBox();
	}

	effect->Render();
}

void CItems::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ITEM_TYPE_COIN:
		break;
	case ITEM_TYPE_LEAF:
		break;
	}
}

void CItems::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	startY = y;
	effect->SetPosition(x, y);
}

void CItems::CoinUpdate(DWORD dt)
{
	CGameObject::Update(dt);

	if (vy != 0)
	{
		vy += ITEM_COIN_GRAVITY * dt;
		if (y > startY)
		{
			this->enable = false;
			effect->StartTimeAppear();
		}
	}

	y += dy;
}

void CItems::LeafUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (vy != 0)
	{
		vy += ITEM_LEAF_GRAVITY * dt;

		if (vy > 0)
		{
			vx += ITEM_LEAF_VELOCITY_X * dt * nx;
			if (vx > ITEM_LEAF_MAX_VELOCITY || vx < -ITEM_LEAF_MAX_VELOCITY) nx = -nx;
		}
	}

	x += dx;
	y += dy;
}