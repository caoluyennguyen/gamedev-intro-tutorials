#include "Items.h"
#include "Ground.h"
#include "Brick.h"
#include "Pipe.h"
#include "Mario.h"
#include "PlayScence.h"
#include "Hud.h"

CItems::CItems(int type)
{
	SetState(type);
	ani = ITEM_ANI_COIN;
	effect = new CEffect();
	if (state == ITEM_TYPE_SWITCH_BLOCK_UP)
	{
		effect->SetState(EFFECT_TYPE_TRANSFORM);
	}
	else if (state == ITEM_TYPE_RED_MUSROOM)
	{
		effect->SetState(EFFECT_TYPE_SCORE_1000);
	}
	else if (state == ITEM_TYPE_GREEN_MUSROOM)
	{
		effect->SetState(EFFECT_TYPE_LEVEL_UP);
	}
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
	else if (state == ITEM_TYPE_SWITCH_BLOCK_DOWN)
	{
		left = top = right = bottom = 0;
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
		else if (state == ITEM_TYPE_LEAF) LeafUpdate(dt);
		else if (state == ITEM_TYPE_RED_MUSROOM || state == ITEM_TYPE_GREEN_MUSROOM) MusroomUpdate(dt, coObjects);
		else SwitchBlockUpdate(dt);
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
		else if (state == ITEM_TYPE_SWITCH_BLOCK_UP) {
			ani = ITEM_ANI_SWITCH_BLOCK_UP;
		}
		else if (state == ITEM_TYPE_SWITCH_BLOCK_DOWN) {
			ani = ITEM_ANI_SWITCH_BLOCK_DOWN;
		}

		animation_set->at(ani)->Render(x, y);
	}

	if (state == ITEM_TYPE_SWITCH_BLOCK_UP) {
		effect->RenderOneTime();
	}
	else effect->Render();
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
	case ITEM_TYPE_RED_MUSROOM:
		appear = true;
		break;
	case ITEM_TYPE_GREEN_MUSROOM:
		appear = true;
	case ITEM_TYPE_SWITCH_BLOCK_UP:
		break;
	}
}

void CItems::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	startY = y;
}

void CItems::CoinUpdate(DWORD dt)
{
	CGameObject::Update(dt);

	if (vy != 0)
	{
		vy += ITEM_COIN_GRAVITY * dt;
		if (y > startY)
		{
			SetEnable(false);
			effect->SetPosition(x, y);
			effect->StartTimeAppear();
			HUD::GetInstance()->AddCoin();
		}
	}

	y += dy;
}

void CItems::LeafUpdate(DWORD dt)
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

void CItems::MusroomUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (appear && y > startY - MUSROOM_LIMIT_POS_Y)
	{
		CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

		if (x > mario->x) vx = ITEM_MUSROOM_VELOCITY_X;
		else vx = -ITEM_MUSROOM_VELOCITY_X;

		vy = ITEM_MUSROOM_VELOCITY_Y;
		y += vy * dt;

		return;
	}
	else appear = false;

	vy += ITEM_LEAF_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj) || dynamic_cast<CGround*>(e->obj) || dynamic_cast<CPipe*>(e->obj)) // if e->obj is Goomba 
			{
				x += min_tx * dx + nx * 0.2f;
				y += min_ty * dy + ny * 0.2f;

				if (e->nx != 0)
				{
					vx = -vx;
				}
			}
			else
			{
				x += dx;
				y += dy;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CItems::SwitchBlockUpdate(DWORD dt)
{}
