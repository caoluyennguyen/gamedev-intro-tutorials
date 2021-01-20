#include "BoomerangBro.h"
#include "Ground.h"
#include "Mario.h"
#include "Boomerang.h"
#include "PlayScence.h"

CBoomerangBro::CBoomerangBro() : CEnemy()
{
	changeDirection = 0;
	SetState(BOOMERANG_BRO_STATE_WALKING);

	fBoomerang = new CBoomerang();

	direction = 1;
	startShoot = GetTickCount();
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
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->x > this->x)
	{
		nx = 1;
	}
	else
	{
		nx = -1;
	}
	CEnemy::Update(dt);

	fBoomerang->Update(dt);
	if (fBoomerang->y > y)
	{
		fBoomerang->y = y;
	}
	else if (fBoomerang->y < y - 20.0f)
	{
		fBoomerang->vy = -fBoomerang->vy;
	}

	vy += BOOMERANG_BRO_STATE_GRAVITY * dt;

	if (state == BOOMERANG_BRO_STATE_DIE)
	{
		x += dx * direction;
		y += dy;
		return;
	}

	if (GetTickCount() - changeDirection > BOOMERANG_BRO_TIME_MOVE)
	{
		direction = -direction;
		changeDirection = GetTickCount();
	}

	if (GetTickCount() - startShoot > BOOMERANG_BRO_TIME_FIRST_SHOOT && startShoot != 0)
	{
		fBoomerang->SetPosition(x, y);
		fBoomerang->StartFly();
		fBoomerang->SetDirection(nx);
		startShoot = 0;
		fBoomerang->enable = true;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx * direction;
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
				else x += dx * nx;

				if (e->ny != 0)
				{
					vy = 0;
					y += min_ty * dy + ny * 0.2f;
				}
			}
			else
			{
				x += dx * direction;
			}
			if (dynamic_cast<CBoomerang*>(e->obj))
			{
				CBoomerang* boomerang = dynamic_cast<CBoomerang*>(e->obj);
				if (e->nx != 0 && boomerang->IsFlyBack())
				{
					boomerang->Reset();
					startShoot = GetTickCount();
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBoomerangBro::Render()
{
	//int ani = BOOMERANG_BRO_STATE_WALKING;

	if (state == BOOMERANG_BRO_STATE_DIE)
	{
		animation_set->at(state)->Render(x, y);
	}
	else
	{
		if (nx == 1)
		{
			if (startShoot == 0)
			{
				animation_set->at(BOOMERANG_BRO_ANI_SHOOTING_RIGHT)->Render(x, y);
			}
			else animation_set->at(BOOMERANG_BRO_ANI_WALKING_RIGHT)->Render(x, y);
		}
		else
		{
			if (startShoot == 0)
			{
				animation_set->at(BOOMERANG_BRO_ANI_WALKING_LEFT)->Render(x, y);
			}
			else animation_set->at(BOOMERANG_BRO_ANI_WALKING_LEFT)->Render(x, y);
		}
	}

	CEnemy::Render();
	/*if (fBoomerang->enable)
	{
		fBoomerang->Render();
	}*/
	fBoomerang->Render();
}

void CBoomerangBro::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOOMERANG_BRO_STATE_WALKING:
		vx = BOOMERANG_BRO_STATE_VELOCITY;
		break;
	case BOOMERANG_BRO_STATE_DIE:
		vx = 0;
		vy = -0.1f;
		break;
	}
}
