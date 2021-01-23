#include "MarioWorldMap.h"
#include "CheckPoint.h"

CMarioWorldMap::CMarioWorldMap()
{
	/*CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(0);*/

	isMoving = false;
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
			float a_left, a_top, a_right, a_bottom;
			obj->GetBoundingBox(a_left, a_top, a_right, a_bottom);

			float b_left, b_top, b_right, b_bottom;
			GetBoundingBox(b_left, b_top, b_right, b_bottom);

			CCheckPoint* checkPoint = dynamic_cast<CCheckPoint*>(obj);

			if (CheckCollision(a_left, a_top, a_right, a_bottom)) {
				if (checkPoint->IsEnable())
				{
					if (vx > 0)
					{
						if (b_right > a_right)
						{
							vx = 0;
							isMoving = false;
							checkPoint->enable = false;
						}
					}
					else if (vx < 0)
					{
						if (b_left < a_left)
						{
							vx = 0;
							isMoving = false;
							checkPoint->enable = false;
						}
					}
					else if (vy < 0)
					{
						if (b_top < a_top)
						{
							vy = 0;
							isMoving = false;
							checkPoint->enable = false;
						}
					}
					else if (vy > 0)
					{
						if (b_bottom > a_bottom)
						{
							vy = 0;
							isMoving = false;
							checkPoint->enable = false;
						}
					}
				}

				checkPoint->GetDirection(moveLeft, moveUp, moveRight, moveDown);
			}
			else
			{
				if (!checkPoint->IsEnable()) checkPoint->enable = true;
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