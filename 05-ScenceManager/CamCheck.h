#pragma once
#include "GameObject.h"

class CCamCheck
{
	float x, vx;
public:
	CCamCheck() { x = 0; vx = 0.1f; }
	void Update(DWORD dt) { x += vx * dt; }

	float GetX() { return x; }
};

