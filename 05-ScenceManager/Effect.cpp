#include "Effect.h"
#include "Hud.h"

CEffect::CEffect()
{
	this->x = x;
	this->y = y;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	ani_set = animation_sets->Get(EFFECT_SCORE_ANI_SET);

	appear = false;
}

void CEffect::Update(DWORD dt)
{
	if (appear)
	{
		if (state == EFFECT_TYPE_HIT)
		{
			if (GetTickCount() - appear_start > HIT_EFFECT_TIME_APPEAR)
			{
				appear = false;
				appear_start = 0;
			}
		}
		else if (GetTickCount() - appear_start > EFFECT_TIME_APPEAR && state < 3)
		{
			appear = false;
			appear_start = 0;

			if (state == EFFECT_TYPE_SCORE_100) HUD::GetInstance()->AddScore(100);
			if (state == EFFECT_TYPE_SCORE_1000) HUD::GetInstance()->AddScore(1000);
		}
		else
		{
			if (state != EFFECT_TYPE_TRANSFORM) y += EFFECT_VELOCITY * dt;
		}
	}
}

void CEffect::Render()
{
	if (appear)
	{
		ani_set->at(state)->Render(x, y);
	}
}

void CEffect::RenderOneTime()
{
	ani_set->at(state)->RenderOneTime(x, y);
}

void CEffect::SetState(int state)
{ 
	this->state = state; 

	switch (state)
	{
	case EFFECT_TYPE_TRANSFORM:
		break;
	default:
		break;
	}
}