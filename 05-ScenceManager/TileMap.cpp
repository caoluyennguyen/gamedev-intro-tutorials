#include "TileMap.h"
#include "Textures.h"
#include "Game.h"

CTileMap::CTileMap()
{
	
}

void CTileMap::Render()
{
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(10);

	float l, t, r, b;

	rect.left = 0;
	rect.top = 0;
	rect.right = 2819;
	rect.bottom = 430;

	CGame::GetInstance()->Draw(0, 0, bbox, rect.left, rect.top, rect.right, rect.bottom);
}