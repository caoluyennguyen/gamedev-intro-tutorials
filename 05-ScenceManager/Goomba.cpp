#include "Goomba.h"
#include "Ground.h"
#include "Brick.h"
#include "Mario.h"
#include "Koopas.h"

CGoomba::CGoomba(int state) : CEnemy()
{
	disappear = 0;
	SetState(state);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y + GOOMBA_BBOX_HEIGHT_DIE;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
	{
		top = y + GOOMBA_BBOX_HEIGHT_DIE;
		bottom = top;
	}
	else
	{
		top = y;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	//CGameObject::Update(dt);

	if (disappear)
	{
		if (GetTickCount() - disappear > TIME_APPEAR)
		{
			enable = false;
		}
	}

	if (GetTickCount() - jump > TIME_JUMP_HIGH)
	{
		isAbleToJump = true;
	}

	CEnemy::Update(dt);

	if (x < 0) vx = abs(vx);

	vy += GOOMBA_GRAVITY * dt;

	if (state == GOOMBA_STATE_DIE_NGUA)
	{
		x += dx;
		y += dy;
		return;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
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

			if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->nx != 0)
				{
					vx = -vx;
					x += min_tx * dx + nx * 0.5f;
				}
				if (e->ny != 0)
				{
					
					if (state == GOOMBA_STATE_FLY)
					{
						if (isAbleToJump)
						{
							vy = -0.2f;
							isAbleToJump = false;
							jump = GetTickCount();
						}
						else vy = -0.1f;
					}
					else
					{
						vy = 0;
						y += min_ty * dy + ny * 0.2f;
					}
				}
			}
			else if (dynamic_cast<CPipe*>(e->obj))
			{
				if (e->nx != 0)
				{
					vx = -vx;
					x += min_tx * dx + nx * 0.5f;
				}
				if (e->ny != 0)
				{
					
					if (state == GOOMBA_STATE_FLY)
					{
						if (isAbleToJump)
						{
							vy = -0.2f;
							isAbleToJump = false;
							jump = GetTickCount();
						}
						else vy = -0.1f;
					}
					else
					{
						vy = 0;
						y += min_ty * dy + ny * 0.2f;
					}
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx != 0)
				{
					vx = -vx;
					x += min_tx * dx + nx * 0.5f;
				}
				if (e->ny != 0)
				{
					if (e->obj->vy != 0)
					{
						SetState(GOOMBA_STATE_DIE_NGUA);
					}
					vy = 0;
				}
			}
			else if (dynamic_cast<CKoopas*>(e->obj) || dynamic_cast<CGoomba*>(e->obj))
			{
				x += dx;
				if (e->obj->state != KOOPAS_STATE_ROLLING && e->obj->state != KOOPAS_STATE_ROLLING_NGUA)
				{
					vx = -vx;
					e->obj->vx = -e->obj->vx;
				}
				//else SetState(GOOMBA_STATE_DIE_NGUA);
				if (state == GOOMBA_STATE_FLY) y += dy;
			}
			else if (dynamic_cast<CMario*>(e->obj))
			{
				if (e->nx != 0)
				{
					x += dx;
				}

				if (e->ny != 0)
				{
					y += dy;
				}
			}
			else
			{
				x += dx;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}
	else if (state == GOOMBA_STATE_DIE_NGUA) {
		ani = GOOMBA_ANI_DIE_NGUA;
	}
	else if (state == GOOMBA_STATE_FLY) {
		ani = GOOMBA_ANI_FLY;
	}

	animation_set->at(ani)->Render(x,y);

	CEnemy::Render();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			vx = 0;
			vy = 0;
			StartDisappear();
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_DIE_NGUA:
			vy = -0.2f;
			vx = nx * 0.01f;
			StartDisappear();
			break;
		case GOOMBA_STATE_FLY:
			jump = GetTickCount();
			vx = -GOOMBA_WALKING_SPEED;
			break;
	}
}
