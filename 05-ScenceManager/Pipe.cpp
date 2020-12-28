#include "Pipe.h"

void CPipe::Render()
{
	animation_set->at(state)->Render(x, y);

	RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (state == PIPE_STATE_SECRET_BLACK_DOWN || state == PIPE_STATE_SECRET_BLACK_UP)
	{
		right = left + PIPE_WIDTH;
		bottom = top + PIPE_BLACK_HEIGHT;
	}
	else
	{
		right = left + PIPE_WIDTH;
		bottom = top + PIPE_HEIGHT;
	}
}