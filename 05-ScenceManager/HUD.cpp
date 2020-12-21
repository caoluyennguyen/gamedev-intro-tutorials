#include "HUD.h"

void HUD::LoadResource()
{

}

void HUD::Render()
{
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(10);

	float l, t, r, b;

	rect.left = 11;
	rect.top = 127;
	rect.right = 164;
	rect.bottom = 157;

	CGame::GetInstance()->Draw(0, 200, bbox, rect.left, rect.top, rect.right, rect.bottom, 255, 0);
}