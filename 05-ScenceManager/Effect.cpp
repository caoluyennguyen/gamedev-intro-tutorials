#include "Effect.h"

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
		if (GetTickCount() - appear_start > EFFECT_TIME_APPEAR)
		{
			appear = false;
			appear_start = 0;
		}
		else
		{
			y -= 0.1f * dt; // hard code
		}
	}

}

void CEffect::Render()
{
	if (appear)
	{
		ani_set->at(EFFECT_TYPE_SCORE_100)->Render(x, y);
	}
}