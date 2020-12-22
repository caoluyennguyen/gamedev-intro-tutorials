#include "HUD.h"

void HUD::LoadResource()
{

}

void HUD::Render()
{
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(10);

	float l, t, r, b;

	rect.left = 0;
	rect.top = 120;
	rect.right = 264;
	rect.bottom = 157;

	CGame::GetInstance()->Draw(0, 200, bbox, rect.left, rect.top, rect.right, rect.bottom, 255, 0);
}