#pragma once
#include "GameObject.h"
#include "Mario.h"

#define CAMERA_VELOCITY	0.02f

class CCamCheck
{
	float x, vx;
	CMario* mario;
public:
	CCamCheck() { x = 0; vx = CAMERA_VELOCITY; }
	void Update(DWORD dt);

	float GetX() { return x; }
	void SetPlayer(CMario* mario) { this->mario = mario; }
};
