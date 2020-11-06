#include "Brick.h"

CBrick::CBrick(int initialPosY)
{
	this->initialPosY = initialPosY;
	freeze = false;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
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
}

void CBrick::Render()
{
	if (state == BRICK_STATE_AVAILABLE)
	{
		animation_set->at(BRICK_ANI_AVAILABLE)->Render(x, y);
	}
	else {
		animation_set->at(BRICK_ANI_UNAVAILABLE)->Render(x, y);
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
		break;
	default:
		break;
	}
}