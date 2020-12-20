#include "Brick.h"

CBrick::CBrick(int initialPosX, int initialPosY, int itemType)
{
	this->initialPosX = initialPosX;
	this->initialPosY = initialPosY;
	freeze = false;
	breakable = false;

	InitItem(itemType);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BRICK_STATE_BREAK)
	{
		if (pieces != NULL) pieces->Update(dt);
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

	if (state == BRICK_STATE_UNAVAILABLE)
	{
		item->Update(dt, coObjects);
	}
}

void CBrick::Render()
{
	if (state == BRICK_STATE_BREAK)
	{
		if (breakable == true && pieces != NULL)
		{
			if (pieces->GetStartTimeRender() == 0)
				pieces->SetStartTimeRender(GetTickCount());
			else if (GetTickCount() - pieces->GetStartTimeRender() > 2000)
			{
				delete pieces;
				pieces = NULL;
				return;
			}

			pieces->Render();
		}
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
		item->SetEnable(true);
		item->SetSpeedVy(-0.2f);
		vy = -0.2f;
		break;
	case BRICK_STATE_BREAKABLE:
		InitPieces();
		breakable = true;
		break;
	default:
		break;
	}
}

void CBrick::InitItem(int itemType)
{
	item = new CItems(itemType);
	item->SetEnable(false);
	item->SetPosition(initialPosX + 3.0f, initialPosY - 16.0f); // hard code
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ITEM_ANIM_SET_ID);

	item->SetAnimationSet(ani_set);
}

void CBrick::InitPieces()
{
	pieces = new BrickPieces(this->initialPosX, this->initialPosY);
}