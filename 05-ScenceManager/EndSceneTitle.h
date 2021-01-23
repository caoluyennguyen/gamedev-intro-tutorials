#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "Game.h"
#include "Animations.h"
#include "PlayCard.h"
#include "Effect.h"

#define SHOW_TIME	100
#define CHANGE_SCENE_TIME	2000

#define FIRST_TITLE_ID		250
#define SECOND_TITLE_ID		251

#define CARD_POS_X	200
#define CARD_POS_Y	70

class CEndSceneTitle
{
	LPSPRITE firstTitle;
	LPSPRITE secondTitle;
	CPlayCard* card;
	CEffect* effect;

	bool enable;
	bool effectStart;
	bool changeSceneStart;
	DWORD title_start;
	DWORD effect_start;
	DWORD change_scene_start;
public:
	void LoadResource();
	void Render();
	void SetCard(int state) { this->card->SetState(state); }
};

