#include "HUD.h"

HUD* HUD::__instance = NULL;

HUD::HUD()
{
	gameTime = 300.0f;
	score = 0;
	coin = 0;
	marioPower = 0;
	endScene = false;
}

void HUD::LoadResource()
{
	speedUp = CSprites::GetInstance()->Get(201);
	speedDown = CSprites::GetInstance()->Get(202);
	power = CAnimationSets::GetInstance()->Get(8);

	vector<LPSPRITE> numbers;
	for (int i = 0; i < 10; i++)
	{
		numbers.push_back(CSprites::GetInstance()->Get(1000 + i));
	}

	for (int i = 0; i < 7; i++)
	{
		number.push_back(numbers);
	}

	card = new CPlayCard();
	card->SetState(0);
	card->SetPosition(172, 207);

	endTitle = new CEndSceneTitle();
	endTitle->LoadResource();
}

void HUD::UnLoadResource()
{
	number.clear();
	endScene = false;
}

void HUD::Update(DWORD dt)
{
	//gameTime += dt / 100;
	gameTime -= TIME_UNIT;
	if (gameTime < 0) gameTime = GAME_TIME;
}

void HUD::Render()
{
	CSprites::GetInstance()->Get(BACKGROUND_SPRITES_ID)->Draw(0, BACKGROUND_POS_Y, COLOR_CODE, 0);

	RenderScore(score);
	RenderTime(gameTime);
	RenderCoin(coin);
	RenderPower();

	card->Render();

	if (endScene) endTitle->Render();
}

void HUD::RenderScore(int numScore)
{
	if (numScore > MAX_SCORE) return;

	for (int i = 0; i < NUM_OF_SCORE; i++)
	{
		int k = numScore % NUMBER_UNIT;
		number[i][k]->Draw(SCORE_POS_X - i * SCORE_POS_X_UNIT, SCORE_POS_Y, COLOR_CODE, 0);
		numScore = (numScore - k) / NUMBER_UNIT;
	}
}

void HUD::RenderTime(int time)
{
	if (time < 0) return;

	for (int i = 0; i < 3; i++)
	{
		int k = time % NUMBER_UNIT;
		number[i][k]->Draw(TIME_POS_X - i * TIME_POS_X_UNIT, TIME_POS_Y, COLOR_CODE, 0);
		time = (time - k) / NUMBER_UNIT;
	}
}

void HUD::RenderCoin(int coin)
{
	if (coin < 0) return;

	for (int i = 0; i < NUM_OF_COIN; i++)
	{
		int k = coin % NUMBER_UNIT;
		number[i][k]->Draw(COIN_POS_X - i * COIN_POS_X_UNIT, COIN_POS_Y, COLOR_CODE, 0);
		coin = (coin - k) / NUMBER_UNIT;
	}
}

void HUD::RenderPower()
{
	if (marioPower < 0)
	{
		marioPower = 0;
	}

	for (int i = 0; i < 6; i++)
	{
		speedDown->Draw(POWER_POS_X + i * POWER_POS_X_UNIT, POWER_POS_Y, COLOR_CODE, 0);
	}

	for (int i = 0; i < marioPower; i++)
	{
		speedUp->Draw(POWER_POS_X + i * POWER_POS_X_UNIT, POWER_POS_Y, COLOR_CODE, 0);
	}

	if (marioPower > 6)
	{
		marioPower = 7;
		power->at(2)->Render(POWER_MAX_POS_X, POWER_POS_Y, COLOR_CODE, 0);
	}
	else
	{
		power->at(1)->Render(POWER_MAX_POS_X, POWER_POS_Y, COLOR_CODE, 0);
	}

}

void HUD::PowerUp()
{
	if (GetTickCount() - powerUp > TIME_POWER)
	{
		marioPower++;
		powerUp = GetTickCount();
	}
}

void HUD::PowerDown()
{
	if (GetTickCount() - powerDown > TIME_POWER)
	{
		marioPower--;
		powerDown = GetTickCount();
	}
}

HUD* HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD();
	return __instance;
}