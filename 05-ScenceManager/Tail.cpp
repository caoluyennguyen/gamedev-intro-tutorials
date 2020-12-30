#include "Tail.h"
#include "Koopas.h"
#include "Brick.h"
#include "Venus.h"
#include "Goomba.h"

Tail::Tail() 
{
	enable = false; 
	effect = new CEffect();
	effect->SetState(EFFECT_TYPE_HIT);
}

void Tail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + TAIL_BBOX_WIDTH;
	bottom = y + TAIL_BBOX_HEIGHT;
}

void Tail::Render()
{
	effect->Render();
	RenderBoundingBox();
}

void Tail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);

		if (dynamic_cast<CKoopas*>(obj)) {
			float kLeft, kTop, kRight, kBottom;
			obj->GetBoundingBox(kLeft, kTop, kRight, kBottom);

			CKoopas* koopas = dynamic_cast<CKoopas*>(obj);
			if (CheckCollision(kLeft, kTop, kRight, kBottom))
			{
				obj->SetState(KOOPAS_STATE_DIE_NGUA);
				effect->SetPosition(x, y);
				effect->StartTimeAppear();
			}
		}
		else if (dynamic_cast<CGoomba*>(obj)) {
			float kLeft, kTop, kRight, kBottom;
			obj->GetBoundingBox(kLeft, kTop, kRight, kBottom);

			if (CheckCollision(kLeft, kTop, kRight, kBottom))
			{
				obj->SetState(GOOMBA_STATE_DIE_NGUA);
				effect->SetPosition(x, y);
				effect->StartTimeAppear();
			}
		}
		else if (dynamic_cast<CBrick*>(obj)) {
			float kLeft, kTop, kRight, kBottom;
			obj->GetBoundingBox(kLeft, kTop, kRight, kBottom);

			if (CheckCollision(kLeft, kTop, kRight, kBottom))
			{
				if (obj->GetState() == BRICK_STATE_AVAILABLE)
				{
					obj->SetState(BRICK_STATE_UNAVAILABLE);
				}
				else if (obj->GetState() == BRICK_STATE_BREAKABLE)
				{
					obj->SetState(BRICK_STATE_BREAK);
				}
			}
		}
		else if (dynamic_cast<CVenus*>(obj)) {
			float kLeft, kTop, kRight, kBottom;
			obj->GetBoundingBox(kLeft, kTop, kRight, kBottom);

			if (CheckCollision(kLeft, kTop, kRight, kBottom) && obj->GetState() != VENUS_STATE_DIE)
			{
				obj->SetState(VENUS_STATE_DIE);
				effect->SetPosition(x, y);
				effect->StartTimeAppear();
			}
		}
	}
	effect->Update(dt);
}