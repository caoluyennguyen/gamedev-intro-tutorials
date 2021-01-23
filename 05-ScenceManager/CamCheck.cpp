#include "CamCheck.h"

CCamCheck::CCamCheck(int x, int maxX) 
{
	this->x = x;
	this->maxX = maxX; 
	vx = CAMERA_VELOCITY; 
	available = true; 
}

void CCamCheck::Update(DWORD dt)
{
	x += vx * dt;

	if (x > maxX)
	{
		available = false;
		return;
	}
	
	if (mario->x < x)
	{
		mario->x = x;
		mario->SetMoveCamera(true);
	}
	else
	{
		mario->SetMoveCamera(false);
	}
}