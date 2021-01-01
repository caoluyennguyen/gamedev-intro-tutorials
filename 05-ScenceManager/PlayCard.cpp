#include "PlayCard.h"

CPlayCard::CPlayCard()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(CARD_ANIM_SET_ID);

	SetAnimationSet(ani_set);
}

void CPlayCard::Render()
{
	this->animation_set->at(state)->Render(x, y, 255, 0);
}