#include "EndSceneTitle.h"

void CEndSceneTitle::LoadResource()
{
	firstTitle = CSprites::GetInstance()->Get(FIRST_TITLE_ID);
	secondTitle = CSprites::GetInstance()->Get(SECOND_TITLE_ID);

	card = new CPlayCard();
	card->SetPosition(CARD_POS_X, CARD_POS_Y);

	enable = true;
	title_start = 0;
	effect_start = 0;

	effectStart = changeSceneStart = false;
	effect = new CEffect();
	effect->SetState(EFFECT_TYPE_LEVEL_UP);
	effect->SetAppear(true);
}

void CEndSceneTitle::Render()
{
	firstTitle->Draw(FIRST_TITLE_POS_X, FIRST_TITLE_POS_Y, COLOR_CODE, 0);
	if (title_start == 0)
	{
		title_start = GetTickCount();
	}
	else
	{
		if (GetTickCount() - title_start > SHOW_TIME)
		{
			secondTitle->Draw(SECOND_TITLE_POS_X, SECOND_TITLE_POS_Y, COLOR_CODE, 0);
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
			//effect->RenderFreeze();
			if (!changeSceneStart)
			{
				changeSceneStart = true;
				change_scene_start = GetTickCount();
			}
		}
	}

	if (change_scene_start != 0)
	{
		if (GetTickCount() - change_scene_start > CHANGE_SCENE_TIME)
		{
			CGame::GetInstance()->SwitchScene(2);
		}
	}
}
