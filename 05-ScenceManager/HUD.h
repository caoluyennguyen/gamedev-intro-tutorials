#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "Game.h"

class HUD
{
	vector<LPSPRITE> speed;
public:
	HUD() {};
	~HUD() {};

	void LoadResource();
	void UnLoadResource();
	void Update(DWORD dt);
	void Render();
};

