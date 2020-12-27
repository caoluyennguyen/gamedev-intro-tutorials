#include "MarioWorldMap.h"

CMarioWorldMap::CMarioWorldMap()
{
	/*CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(0);*/
}

void CMarioWorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;
}

void CMarioWorldMap::Render()
{
	animation_set->at(0)->Render(x, y);

	RenderBoundingBox();
}

void CMarioWorldMap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARIO_BBOX_WIDTH;
	b = y + MARIO_BBOX_HEIGHT;
}