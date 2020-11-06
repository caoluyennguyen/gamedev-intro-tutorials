#include "Ground.h"

CGround::CGround(float l, float t, float r, float b, int id)
{
	x = l;
	y = t;
	width = r - l;
	height = b - t;
	this->id = id;
}

void CGround::Render()
{
	RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}