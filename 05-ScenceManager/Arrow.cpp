#include "Arrow.h"

CArrow::CArrow()
{
	/*CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(0);*/

	isMoving = false;
}

void CArrow::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;
}

void CArrow::Render()
{
	animation_set->at(0)->Render(x, y);

	RenderBoundingBox();
}