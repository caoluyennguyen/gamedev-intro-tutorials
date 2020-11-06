#pragma once
#include "GameObject.h"

#define GROUND_TYPE_NORMAL		0
#define GROUND_TYPE_JUMP_OVER	1

class CGround : public CGameObject
{
	int width;
	int height;
	int id;
public:
	CGround(float l, float t, float r, float b, int id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom) {};

	int GetId() { return id; }
};

