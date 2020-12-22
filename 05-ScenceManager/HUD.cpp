#include "HUD.h"

void HUD::LoadResource()
{
	bbox = CTextures::GetInstance()->Get(10);

	rect.left = 0;
	rect.top = 120;
	rect.right = 264;
	rect.bottom = 157;

	for (int i = 0; i < 6; i++)
	{
		speedUp.push_back(new CSprite(100, 63, 161, 72, 170, bbox));
	}

	for (int i = 0; i < 6; i++)
	{
		speedDown.push_back(new CSprite(101, 90, 161, 99, 170, bbox));
	}
}

void HUD::Render()
{
	CGame::GetInstance()->Draw(0, 200, bbox, rect.left, rect.top, rect.right, rect.bottom, 255, 0);

	for (int i = 0; i < marioSpeed; i++)
	{
		speedUp[i]->Draw(70 + i * 5, 220, 255, 0);
	}

	speedDown[0]->Draw(100, 220, 255, 0);
}