#include "EndPoint.h"

CEndPoint::CEndPoint() 
{
	state = 2; 
	rolling_start = GetTickCount();
}

void CEndPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == ENDPOINT_STATE_EMPTY)
	{
		effect->Update(dt);
		return;
	}

	if (GetTickCount() - rolling_start > ROLLING_DEFAULT_TIME)
	{
		state++;
		StartRolling();
	}

	if (state > 2) state = 0;
}

void CEndPoint::Render()
{
	animation_set->at(state)->Render(x, y);

	if (state == ENDPOINT_STATE_EMPTY) effect->Render();

	RenderBoundingBox();
}

void CEndPoint::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + ENDPOINT_BBOX_WIDTH;
	bottom = top + ENDPOINT_BBOX_HEIGHT;
}

void CEndPoint::StartEffect()
{
	if (effect == NULL)
	{
		effect = new CEffect();
		effect->SetPosition(this->x, this->y);
		effect->SetState(state + 3);
		effect->StartTimeAppear();
	}
	
	SetState(ENDPOINT_STATE_EMPTY);
}