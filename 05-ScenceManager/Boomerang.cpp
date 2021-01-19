#include "Boomerang.h"
#include "Ground.h"

CBoomerang::CBoomerang()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(BOOMERANG_ANIM_SET_ID);

	SetAnimationSet(ani_set);

	fly_x = GetTickCount();
	vx = BOOMERANG_VELOCITY;
}

void CBoomerang::Update(DWORD dt)
{
	if (GetTickCount() - fly_x > BOOMERANG_TIME_X && fly_x != 0)
	{
		vx = -vx;
		fly_x = 0;
	}

	this->dt = dt;
	dx = vx * nx * dt;
	dy = vy * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	//if (enable) CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//	y += dy;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;
	//	float rdx = 0;
	//	float rdy = 0;

	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	//
	//	// Collision logic with other objects
	//	//
	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];
	//		if (dynamic_cast<CGround*>(e->obj)) // if e->obj is Goomba 
	//		{
	//			x += min_tx * dx + nx * 0.2f;
	//			y += min_ty * dy + ny * 0.2f;
	//		}
	//	}
	//}

	//// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBoomerang::Render()
{
	animation_set->at(3)->Render(x, y);

	RenderBoundingBox();
}

void CBoomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOOMERANG_BBOX_WIDTH;
	b = y + BOOMERANG_BBOX_HEIGHT;
}