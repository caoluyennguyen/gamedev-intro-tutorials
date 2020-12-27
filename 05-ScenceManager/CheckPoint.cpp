#include "CheckPoint.h"

CCheckPoint::CCheckPoint(int left, int right, int bottom, int top)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
}

void CCheckPoint::Render()
{
	animation_set->at(1)->Render(x, y);

	RenderBoundingBox();
}

void CCheckPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CHECKPOINT_BBOX_WIDTH;
	b = y + CHECKPOINT_BBOX_HEIGHT;
}