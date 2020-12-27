#include "MarioWorldMap.h"
#include "CheckPoint.h"

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

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		// Check AABB collision
		LPGAMEOBJECT obj = coObjects->at(i);
		
		if (dynamic_cast<CCheckPoint*>(obj)) {
			float kLeft, kTop, kRight, kBottom;
			obj->GetBoundingBox(kLeft, kTop, kRight, kBottom);

			if (CheckCollision(kLeft, kTop, kRight, kBottom)) {
				vx = vy = 0;
			}
		}
	}
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