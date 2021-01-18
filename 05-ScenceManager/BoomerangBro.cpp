#include "BoomerangBro.h"
#include "Ground.h"
#include "Mario.h"

CBoomerangBro::CBoomerangBro() : CEnemy()
{
	changeDirection = 0;
	SetState(BOOMERANG_BRO_STATE_WALKING);

	boomerang = new CBoomerang();
	boomerang->SetPosition(x, y);
}

void CBoomerangBro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + BOOMERANG_BRO_BBOX_WIDTH;

	if (state == BOOMERANG_BRO_STATE_DIE)
	{
		top = y;
		bottom = top;
	}
	else
	{
		top = y;
		bottom = top + BOOMERANG_BRO_BBOX_HEIGHT;
	}
}

void CBoomerangBro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	CEnemy::Update(dt);

	//vy += BOOMERANG_BRO_STATE_GRAVITY * dt;

	if (state == BOOMERANG_BRO_STATE_DIE)
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

					vy = 0;
					y += min_ty * dy + ny * 0.2f;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBoomerangBro::Render()
{
	int ani = BOOMERANG_BRO_STATE_WALKING;

	animation_set->at(ani)->Render(x, y);

	CEnemy::Render();
	boomerang->Render();
}

void CBoomerangBro::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOOMERANG_BRO_STATE_DIE:
		vx = 0;
		vy = -0.1f;
		break;
	}
}
