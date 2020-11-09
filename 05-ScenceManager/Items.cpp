#include "Items.h"

CItems::CItems(int type)
{
	this->type = type;
	SetState(ITEM_TYPE_COIN);
	ani = ITEM_ANI_COIN;
	effect = new CEffect();
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
	if (enable)
	{
		CGameObject::Update(dt, coObjects);

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

	effect->Update(dt);
}

void CItems::Render()
{
	if (enable)
	{
		if (state == ITEM_TYPE_COIN) {
			ani = ITEM_ANI_COIN;
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
		vx = 0;
		vy = 0;
		break;
	}
}

void CItems::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	startY = y;
	effect->SetPosition(x, y);
}