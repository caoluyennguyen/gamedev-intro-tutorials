#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "Game.h"
#include "Animations.h"
#include "PlayCard.h"

#define TIME_PLAY 300

class HUD
{
	static HUD* __instance;

	RECT rect;
	LPDIRECT3DTEXTURE9 bbox;

	int marioSpeed;
	float gameTime;
	int score;
	int coin;

	LPSPRITE speedUp;
	LPSPRITE speedDown;
	LPANIMATION_SET power;
	CPlayCard* card;

	vector<vector<LPSPRITE>> number;
public:
	HUD();
	~HUD() {};

	void LoadResource();
	void UnLoadResource();
	void Update(DWORD dt);
	void Render();
	void RenderScore(int score);
	void RenderTime(int time);
	void RenderCoin(int coin);

	void AddScore(int score) { this->score += score; }
	void AddCoin() { this->coin++; }
	void SetCard(int state) { this->card->SetState(state); }

	static HUD* GetInstance();
};