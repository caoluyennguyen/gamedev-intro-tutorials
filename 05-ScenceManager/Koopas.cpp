#include "Koopas.h"
#include "Ground.h"
#include "Mario.h"
#include "Brick.h"
#include <algorithm>
#include "Goomba.h"
#include "Venus.h"


CKoopas::CKoopas(int state, int color) : CEnemy()
{
	SetState(state);
	this->color = color;
	direction = 1;
}

void CKoopas::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;


	if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_DIE_NGUA || state == KOOPAS_STATE_ROLLING || state == KOOPAS_STATE_ROLLING_NGUA)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	CEnemy::Update(dt);

	if (x < 0) vx = abs(vx);

	if (state == KOOPAS_STATE_RED_FLY)
	{
		if (vy > KOOPAS_FLY_MAX_VY) direction = -1;
		else if (vy < -KOOPAS_FLY_MAX_VY) direction = 1;

		vy += KOOPAS_GRAVITY_RED_FLY * dt * direction;
	}
	else vy += KOOPAS_GRAVITY * dt;

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
				CGround* ground = dynamic_cast<CGround*>(e->obj);
				if (e->nx != 0)
				{
					if (ground->GetId() == GROUND_TYPE_NORMAL)
					{
						vx = -vx;
						x += min_tx * dx + nx * 0.5f;
					}
					else
					{
						x += dx;
					}
				}
				if (e->ny < 0)
				{
					if (state == KOOPAS_STATE_FLY) vy = -0.2f;
					else if (state == KOOPAS_STATE_DIE_NGUA)
					{
						vx = 0;
					}
					else vy = 0;

					if (ground->GetId() == GROUND_TYPE_JUMP_OVER)
					{
						vy = 0;
						if (state == KOOPAS_STATE_WALKING)
						{
							if (x < ground->x - KOOPAS_BBOX_WIDTH / 2) vx = KOOPAS_WALKING_SPEED
							else if (x > ground->x + ground->GetWidth() - KOOPAS_BBOX_WIDTH / 2) vx = -KOOPAS_WALKING_SPEED;
						}
						else if (state == KOOPAS_STATE_DIE_NGUA)
						{
							vx = 0;
						}
					}
				}
				else if (e->ny > 0)
				{
					y += dy;
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
					if (state == KOOPAS_STATE_FLY) vy = -0.2f;
					else if (state == KOOPAS_STATE_DIE_NGUA)
					{
						vx = 0;
					}
					else vy = 0;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx != 0)
				{
					if (e->obj->GetState() == BRICK_STATE_BREAK) x += dx;
					else if (e->obj->GetState() == BRICK_STATE_BREAK || e->obj->GetState() == BRICK_STATE_COIN)
					{
						x += dx;
					}
					else
					{
						vx = -vx;
						x += min_tx * dx + nx * 0.5f;
						if (state == KOOPAS_STATE_ROLLING || state == KOOPAS_STATE_ROLLING_NGUA)
						{
							if (e->obj->GetState() == BRICK_STATE_AVAILABLE)
							{
								e->obj->SetState(BRICK_STATE_UNAVAILABLE);
							}
							else if (e->obj->GetState() == BRICK_STATE_BREAKABLE)
							{
								e->obj->SetState(BRICK_STATE_BREAK);
							}
						}
					}
				}
				
				if (e->ny != 0 && e->obj->GetState() != BRICK_STATE_BREAK)
				{
					vy = 0;

					if (state == KOOPAS_STATE_FLY) vy = -0.2f;
					else if (state == KOOPAS_STATE_WALKING)
					{
						if (x < e->obj->x - KOOPAS_BBOX_WIDTH / 2) vx = KOOPAS_WALKING_SPEED
						else if (x > e->obj->x + KOOPAS_BBOX_WIDTH / 2) vx = -KOOPAS_WALKING_SPEED;
					}
					else if (state == KOOPAS_STATE_DIE_NGUA)
					{
						vx = 0;
					}
				}
			}
			else if (dynamic_cast<CMario*>(e->obj))
			{
				x += dx;
				
				if (e->nx != 0)
				{
					vx = -vx;
				}

				if (e->ny != 0)
				{
					vy = 0;
				}
			}
			else if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				x += dx;
				if (state == KOOPAS_STATE_FLY) y += dy;

				if (state == KOOPAS_STATE_ROLLING || state == KOOPAS_STATE_ROLLING_NGUA)
				{
					goomba->SetState(GOOMBA_STATE_DIE_NGUA);
					goomba->ScoreUp();

				}
			}
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				x += dx;
				y += dy;

				if (state == KOOPAS_STATE_WALKING && e->obj->GetState() == KOOPAS_STATE_ROLLING)
				{
					this->SetState(KOOPAS_STATE_DIE_NGUA);
					ScoreUp();
				}
			}
			else if (dynamic_cast<CVenus*>(e->obj))
			{
				x += dx;

				if (e->obj->GetState() != VENUS_STATE_DIE) e->obj->SetState(VENUS_STATE_DIE);
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::Render()
{
	CEnemy::Render();

	int ani = KOOPAS_ANI_WALKING_LEFT;

	if (color == 0)
	{
		if (state == KOOPAS_STATE_DIE) {
			ani = KOOPAS_ANI_DIE;
		}
		else if (state == KOOPAS_STATE_DIE_NGUA) {
			ani = KOOPAS_ANI_DIE_NGUA;
		}
		else if (state == KOOPAS_STATE_ROLLING)
		{
			ani = KOOPAS_ANI_ROLLING;
		}
		else if (state == KOOPAS_STATE_ROLLING_NGUA)
		{
			ani = KOOPAS_ANI_ROLLING_NGUA;
		}
		else if (state == KOOPAS_STATE_FLY)
		{
			if (vx > 0) ani = KOOPAS_ANI_FLY_RIGHT;
			else ani = KOOPAS_ANI_FLY_LEFT;
		}
		else
		{
			if (vx > 0) ani = KOOPAS_ANI_WALKING_RIGHT;
			else ani = KOOPAS_ANI_WALKING_LEFT;
		}
	}
	else
	{
		if (state == KOOPAS_STATE_DIE) {
			ani = KOOPAS_RED_ANI_DIE;
		}
		else if (state == KOOPAS_STATE_DIE_NGUA) {
			ani = KOOPAS_RED_ANI_DIE_NGUA;
		}
		else if (state == KOOPAS_STATE_ROLLING)
		{
			ani = KOOPAS_RED_ANI_ROLLING;
		}
		else if (state == KOOPAS_STATE_ROLLING_NGUA)
		{
			ani = KOOPAS_RED_ANI_ROLLING_NGUA;
		}
		else if (state == KOOPAS_STATE_FLY || state == KOOPAS_STATE_RED_FLY)
		{
			if (vx > 0) ani = KOOPAS_RED_ANI_FLY_RIGHT;
			else ani = KOOPAS_RED_ANI_FLY_LEFT;
		}
		else
		{
			if (vx > 0) ani = KOOPAS_RED_ANI_WALKING_RIGHT;
			else ani = KOOPAS_RED_ANI_WALKING_LEFT;
		}
	}
	
	/*else if (vx > 0) ani = KOOPAS_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = KOOPAS_ANI_WALKING_LEFT;*/

	animation_set->at(ani)->Render(x, y);
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_DIE_NGUA:
		vy = -0.2f;
		vx = nx * 0.01f;
		break;
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_FLY:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_ROLLING:
		vx = nx * KOOPAS_ROLLING_SPEED;
		break;
	case KOOPAS_STATE_ROLLING_NGUA:
		vx = nx * KOOPAS_ROLLING_SPEED;
		break;
	}
}