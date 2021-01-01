#include "Turtle.h"

CTurtle::CTurtle() 
{
	vx = 0.01f;
	startX = x;
}

void CTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;

	if (vx > 0)
	{
		if (x > startX + 20.0f)
		{
			vx = -vx;
			startX = x;
		}
	}
	else
	{
		if (x < startX - 20.0f)
		{
			vx = -vx;
			startX = x;
		}
	}
}

void CTurtle::Render()
{
	if (vx > 0) animation_set->at(0)->Render(x, y);
	else animation_set->at(1)->Render(x, y);
}