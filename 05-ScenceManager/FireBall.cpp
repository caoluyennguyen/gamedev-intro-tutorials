#include "FireBall.h"
#include "Koopas.h"
#include "Ground.h"
#include "Goomba.h"
#include "Brick.h"

FireBall::FireBall()
{
	vx = FIREBALL_VELOCITY_X;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(FIREBALL_ANIM_SET_ID);

	SetAnimationSet(ani_set);
	enable = false;
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * nx * dt;
	vy += FIREBALL_GRAVITY * dt;
	dy = vy * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (enable) CalcPotentialCollisions(coObjects, coEvents);

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

			if (dynamic_cast<CKoopas*>(e->obj)) // if e->obj is Goomba 
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

				// jump on top >> kill Koopas and deflect a bit 
				if (e->ny != 0 || e->nx != 0)
				{
					if (koopas->GetState() != KOOPAS_STATE_DIE)
					{
						koopas->SetState(KOOPAS_STATE_DIE);
						enable = false;
					}
				}
			}
			else if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny != 0 || e->nx != 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						enable = false;
					}
				}
			} // if Goomba
			else if (dynamic_cast<CBrick*>(e->obj) || dynamic_cast<CGround*>(e->obj)) // if e->obj is Goomba 
			{
				x += min_tx * dx + nx * 0.2f;
				y += min_ty * dy + ny * 0.2f;

				CBrick* brick = dynamic_cast<CBrick*>(e->obj);

				if (e->ny < 0)
				{
					vy = FIREBALL_VELOCITY_Y;
				}
				else if (e->nx != 0)
				{
					enable = false;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void FireBall::Render()
{
	if (nx > 0)
	{
		animation_set->at(0)->Render(x, y);
	}
	else
	{
		animation_set->at(1)->Render(x, y);
	}

	RenderBoundingBox();
}

void FireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBALL_BBOX_WIDTH;
	b = y + FIREBALL_BBOX_HEIGHT;
}