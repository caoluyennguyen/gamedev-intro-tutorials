#include "CamCheck.h"

void CCamCheck::Update(DWORD dt)
{
	x += vx * dt;

	//CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	
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