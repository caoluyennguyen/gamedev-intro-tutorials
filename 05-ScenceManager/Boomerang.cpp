#include "Boomerang.h"
#include "Ground.h"

CBoomerang::CBoomerang()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(BOOMERANG_ANIM_SET_ID);

	SetAnimationSet(ani_set);

	fly_x = 0;
	vx = BOOMERANG_VELOCITY_X;
	vy = BOOMERANG_VELOCITY_Y;
	flyBack = false;
	enable = false;
}

void CBoomerang::Update(DWORD dt)
{
	if (!enable)
	{
		return;
	}

	dx = vx * direction * dt;
	dy = vy * dt;

	if (GetTickCount() - fly_x > BOOMERANG_TIME_X && fly_x != 0)
	{
		vx = -vx;
		flyBack = true;
		fly_x = 0;
	}
	vy += BOOMERANG_GRAVITY * dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	x += dx;
	y += dy;
}

void CBoomerang::Render()
{
	if (enable) animation_set->at(3)->Render(x, y);

	RenderBoundingBox();
}

void CBoomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOOMERANG_BBOX_WIDTH;
	b = y + BOOMERANG_BBOX_HEIGHT;
}