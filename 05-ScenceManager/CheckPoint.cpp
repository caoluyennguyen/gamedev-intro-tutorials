#include "CheckPoint.h"

CCheckPoint::CCheckPoint(int left, int top, int right, int bottom)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;

	state = CHECKPOINT_STATE_NORMAL;
}

void CCheckPoint::Render()
{
	animation_set->at(state)->Render(x, y);

	RenderBoundingBox();
}

void CCheckPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CHECKPOINT_BBOX_WIDTH;
	b = y + CHECKPOINT_BBOX_HEIGHT;
}