#include "Koopas.h"
#include "Ground.h"
#include "Mario.h"
#include <algorithm>


CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;
	//bottom = y + KOOPAS_BBOX_HEIGHT;


	if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_DIE_NGUA || state == KOOPAS_STATE_ROLLING)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

//void CKoopas::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
//{
//	for (UINT i = 0; i < coObjects->size(); i++)
//	{
//		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));
//
//		if (e->t > 0 && e->t <= 1.0f)
//			coEvents.push_back(e);
//		else
//			delete e;
//
//		// Check AABB collision
//		LPGAMEOBJECT obj = coObjects->at(i);
//	}
//
//	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
//}


void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	CGameObject::Update(dt);

	if (x < 0) vx = abs(vx);

	vy += KOOPAS_GRAVITY * dt;

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
				}
			}
			else if (dynamic_cast<CMario*>(e->obj))
			{
				x += dx;
				//y += dy;
				if (e->ny != 0)
				{
					vy = 0;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING_LEFT;
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
	else if (vx > 0) ani = KOOPAS_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = KOOPAS_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
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
		vx = 0;
		vy = -0.1f;
		break;
	case KOOPAS_STATE_WALKING:
		//vx = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_ROLLING:
		vx = nx * 0.2f;
		break;
	}

}