#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "Game.h"
#include "Animations.h"
#include "PlayCard.h"
#include "EndSceneTitle.h"

#define TIME_PLAY 1000
#define TIME_POWER 150

class HUD
{
	static HUD* __instance;

	RECT rect;
	LPDIRECT3DTEXTURE9 bbox;

	int marioPower;
	float gameTime;
	int score;
	int coin;
	bool endScene;

	LPSPRITE speedUp;
	LPSPRITE speedDown;
	LPANIMATION_SET power;
	CPlayCard* card;
	CEndSceneTitle* endTitle;

	DWORD powerUp;
	DWORD powerDown;

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
	void RenderPower();

	void AddScore(int score) { this->score += score; }
	void AddCoin() { this->coin++; }
	void SetCard(int state) { this->card->SetState(state); endTitle->SetCard(state); }

	void SetEndScene(bool endScene) { this->endScene = endScene; }
	bool IsEndScene() { return this->endScene; }

	void PowerUp();
	void PowerDown();

	static HUD* GetInstance();
};