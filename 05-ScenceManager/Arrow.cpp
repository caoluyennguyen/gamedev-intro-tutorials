#include "Arrow.h"

void CArrow::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y > MAX_Y)
	{
		y = MIN_Y;
	}
	else if (y < MIN_Y)
	{
		y = MAX_Y;
	}
}

void CArrow::Render()
{
	animation_set->at(0)->Render(x, y);
}