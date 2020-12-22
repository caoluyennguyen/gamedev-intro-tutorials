#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "Game.h"

class HUD
{
	RECT rect;
	LPDIRECT3DTEXTURE9 bbox;

	int marioSpeed;
	vector<LPSPRITE> speedUp;
	vector<LPSPRITE> speedDown;
public:
	HUD() { marioSpeed = 3; };
	~HUD() {};

	void LoadResource();
	void UnLoadResource();
	void Update(DWORD dt);
	void Render();
};

