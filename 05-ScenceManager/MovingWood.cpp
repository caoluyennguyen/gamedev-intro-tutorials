#include "MovingWood.h"
#include "Mario.h"

CMovingWood::CMovingWood()
{
	vx = -MOVING_WOOD_SPEED;
	vy = 0;
	fallDown = false;
}

void CMovingWood::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt);
	if (fallDown) vy += MOVING_WOOD_GRAVITY * dt;

	x += dx;
	y += dy; 
}
void CMovingWood::Render()
{
	animation_set->at(state)->Render(x, y);
	RenderBoundingBox();
}

void CMovingWood::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + MOVING_WOOD_WIDTH;
	bottom = top + MOVING_WOOD_HEIGHT;
}