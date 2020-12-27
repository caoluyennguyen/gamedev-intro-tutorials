#include "Grass.h"

void CGrass::Render()
{
	animation_set->at(0)->Render(x, y);
}