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
	gameTime -= 0.01f;
	if (gameTime < 0) gameTime = 300;
}

void HUD::Render()
{
	CSprites::GetInstance()->Get(200)->Draw(0, 200, 255, 0);

	RenderScore(score);
	RenderTime(gameTime);
	RenderCoin(coin);
	RenderPower();

	card->Render();

	if (endScene) endTitle->Render();
}

void HUD::RenderScore(int numScore)
{
	if (numScore > 9999999) return;

	for (int i = 0; i < 7; i++)
	{
		int k = numScore % 10;
		number[i][k]->Draw(118 - i * 9, 223, 255, 0);
		numScore = (numScore - k) / 10;
	}
}

void HUD::RenderTime(int time)
{
	if (time < 0) return;

	for (int i = 0; i < 3; i++)
	{
		int k = time % 10;
		number[i][k]->Draw(152 - i * 7, 223, 255, 0);
		time = (time - k) / 10;
	}
}

void HUD::RenderCoin(int coin)
{
	if (coin < 0) return;

	for (int i = 0; i < 2; i++)
	{
		int k = coin % 10;
		number[i][k]->Draw(151 - i * 10, 214, 255, 0);
		coin = (coin - k) / 10;
	}
}

void HUD::RenderPower()
{
	if (marioPower < 0)
	{
		marioPower = 0;
	}
	
	if (marioPower > 6)
	{
		marioPower = 6;
		power->at(2)->Render(120, 214, 255, 0);
	}
	else
	{
		power->at(1)->Render(120, 214, 255, 0);
	}

	for (int i = 0; i < marioPower; i++)
	{
		speedUp->Draw(60 + i * 10, 214, 255, 0);
	}

	for (int i = 0; i < 6; i++)
	{
		speedDown->Draw(60 + i * 10, 214, 255, 0);
	}

}

void HUD::PowerUp()
{
	if (GetTickCount() - powerUp > TIME_POWER)
	{
		marioPower++;
	}
}

void HUD::PowerDown()
{
	if (GetTickCount() - powerUp > TIME_POWER)
	{
		marioPower--;
	}
}

HUD* HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD();
	return __instance;
}