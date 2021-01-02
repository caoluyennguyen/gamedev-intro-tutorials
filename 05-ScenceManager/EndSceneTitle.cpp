#include "EndSceneTitle.h"

void CEndSceneTitle::LoadResource()
{
	firstTitle = CSprites::GetInstance()->Get(250);
	secondTitle = CSprites::GetInstance()->Get(251);

	card = new CPlayCard();
	card->SetPosition(200, 70);

	enable = true;
	title_start = 0;
	effect_start = 0;

	effectStart = changeSceneStart = false;
	effect = new CEffect();
	effect->SetState(EFFECT_TYPE_LEVEL_UP);
	effect->SetPosition(130, 120);
	effect->SetAppear(true);
}

void CEndSceneTitle::Render()
{
	firstTitle->Draw(50, 20, 255, 0);
	if (title_start == 0)
	{
		title_start = GetTickCount();
	}
	else
	{
		if (GetTickCount() - title_start > SHOW_TIME)
		{
			secondTitle->Draw(50, 70, 255, 0);
			card->Render();
			if (!effectStart)
			{
				effectStart = true;
				effect_start = GetTickCount();
			}
			
		}
	}

	if (effect_start != 0)
	{
		if (GetTickCount() - effect_start > SHOW_TIME * 2)
		{
			effect->RenderFreeze();
			if (!changeSceneStart)
			{
				changeSceneStart = true;
				change_scene_start = GetTickCount();
			}
		}
	}
	

	//if (card_start != 0)
	//{
	//	if (GetTickCount() - card_start > SHOW_TIME)
	//	{
	//		//CGame::GetInstance()->SwitchScene(1);
	//		card->Render();
	//		if (!changeSceneStart)
	//		{
	//			change_scene_start = GetTickCount();
	//			changeSceneStart = true;
	//		}
	//	}
	//}

	if (change_scene_start != 0)
	{
		if (GetTickCount() - change_scene_start > CHANGE_SCENE_TIME)
		{
			CGame::GetInstance()->SwitchScene(1);
		}
	}
}
