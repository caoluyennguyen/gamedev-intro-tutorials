#include "Pipe.h"

void CPipe::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CPipe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + PIPE_WIDTH;
	bottom = top + PIPE_HEIGHT;
}