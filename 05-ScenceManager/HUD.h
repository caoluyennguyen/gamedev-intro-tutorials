#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "Game.h"
#include "Animations.h"
#include "PlayCard.h"
#include "EndSceneTitle.h"

#pragma region define
#define TIME_PLAY 1000
#define TIME_POWER 150
#define TIME_UNIT 0.01f

#define GAME_TIME 300.0f
#define BACKGROUND_SPRITES_ID 200
#define SPEED_UP_SPRITES_ID 201
#define SPEED_DOWN_SPRITES_ID 202
#define NUMBER_SPRITES_ID 1000
#define POWER_ANIM_ID 8

#define NUM_OF_COIN 2
#define NUM_OF_TIME 3
#define NUM_OF_POWER 6
#define NUM_OF_MAX_POWER 7
#define NUM_OF_SCORE 7
#define NUM_OF_POINT 10
#define BACKGROUND_POS_Y 200
#define COLOR_CODE	255
#define NUMBER_UNIT	10
#define MAX_SCORE	9999999
#define SCORE_POS_X	118.0f
#define SCORE_POS_X_UNIT	9.0f
#define SCORE_POS_Y	223.0f
#define CARD_HUD_POS_X 172.0f
#define CARD_HUD_POS_Y 207.0f
#define TIME_POS_X	152.0f
#define TIME_POS_X_UNIT	7.0f
#define TIME_POS_Y	223.0f
#define COIN_POS_X	151.0f
#define COIN_POS_X_UNIT	10.0f
#define COIN_POS_Y	214.0f
#define POWER_POS_X	60.0f
#define POWER_MAX_POS_X	120.0f
#define POWER_POS_X_UNIT	10.0f
#define POWER_POS_Y	214.0f
#pragma endregion



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