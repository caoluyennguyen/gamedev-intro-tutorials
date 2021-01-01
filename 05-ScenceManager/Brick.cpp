#include "Brick.h"

CBrick::CBrick(int initialPosX, int initialPosY, int itemType)
{
	this->initialPosX = initialPosX;
	this->initialPosY = initialPosY;
	freeze = false;
	breakable = false;
	coin_start = 0;

	InitItem(itemType);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	coObjects->push_back(this->item);

	if (state == BRICK_STATE_BREAK)
	{
		if (breakable == true && pieces != NULL)
		{
			if (pieces->GetStartTimeAppear() == 0) pieces->SetStartTimeAppear(GetTickCount());
			else if (GetTickCount() - pieces->GetStartTimeAppear() > 2000)
			{
				delete pieces;
				pieces = NULL;
				return;
			}

			pieces->Update(dt);
		}
		return;
	}

	CGameObject::Update(dt);

	if (!freeze)
	{
		y += dy;
		if (y < initialPosY) vy += BRICK_GRAVITY * dt;
	}
	else {
		vx = vy = 0;
	}

	if (y > initialPosY)
	{
		y = initialPosY;
		freeze = true;
	}

	/*if (state == BRICK_STATE_UNAVAILABLE)
	{
		item->Update(dt, coObjects);
	}*/
}

void CBrick::Render()
{
	if (state == BRICK_STATE_BREAK)
	{
		if (pieces != NULL) pieces->Render();
		return;
	}

	if (state == BRICK_STATE_AVAILABLE)
	{
		animation_set->at(BRICK_ANI_AVAILABLE)->Render(x, y);
	}
	else if (state == BRICK_ANI_UNAVAILABLE) {
		animation_set->at(BRICK_ANI_UNAVAILABLE)->Render(x, y);
		item->Render();
	}
	else if (state == BRICK_STATE_BREAKABLE)
	{
		animation_set->at(BRICK_ANI_BREAKABLE)->Render(x, y);
	}
	else if (state == BRICK_STATE_COIN)
	{
		animation_set->at(BRICK_ANI_COIN)->Render(x, y);
	}

	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CBrick::SetState(int state)
{
	this->state = state;

	switch (state)
	{
	case BRICK_STATE_AVAILABLE:
		break;
	case BRICK_STATE_UNAVAILABLE:
		vy = -0.2f;
		item->SetEnable(true);

		if (item->GetState() == ITEM_TYPE_COIN) item->SetSpeedVy(-ITEM_COIN_VELOCITY);
		else if (item->GetState() == ITEM_TYPE_LEAF) item->SetSpeedVy(-ITEM_LEAF_VELOCITY_Y);

		break;
	case BRICK_STATE_BREAKABLE:
		InitPieces();
		breakable = true;
		break;
	case BRICK_STATE_BREAK:
		enable = false;
		break;
	default:
		break;
	}
}

void CBrick::InitItem(int itemType)
{
	item = new CItems(itemType);
	item->SetEnable(false);
	if (item->GetState() == ITEM_TYPE_RED_MUSROOM || item->GetState() == ITEM_TYPE_GREEN_MUSROOM)
		item->SetPosition(initialPosX, initialPosY);
	if (item->GetState() == ITEM_TYPE_SWITCH_BLOCK_UP)
		item->SetPosition(initialPosX, initialPosY - ITEM_MUSROOM_BBOX_HEIGHT);
	else
		item->SetPosition(initialPosX + ITEM_INITIAL_POS_X, initialPosY - ITEM_INITIAL_POS_Y);
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ITEM_ANIM_SET_ID);

	item->SetAnimationSet(ani_set);
}

void CBrick::InitPieces()
{
	pieces = new BrickPieces(this->initialPosX, this->initialPosY);
}