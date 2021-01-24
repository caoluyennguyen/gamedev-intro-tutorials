#include "CheckPoint.h"

CCheckPoint::CCheckPoint(int left, int top, int right, int bottom, int id)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->sceneId = id;

	state = CHECKPOINT_STATE_NORMAL;
}

void CCheckPoint::Render()
{
	animation_set->at(state)->Render(x, y);
}

void CCheckPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CHECKPOINT_BBOX_WIDTH;
	b = y + CHECKPOINT_BBOX_HEIGHT;
}