#include "ScrollStage.h"

void CScrollStage::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y < -SCROLL_STAGE_MIN_Y) return;
	y -= STAGE_VELOCITY;
}

void CScrollStage::Render()
{
	animation_set->at(0)->Render(x, y);
}