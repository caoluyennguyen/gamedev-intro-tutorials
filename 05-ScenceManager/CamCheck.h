#pragma once
#include "GameObject.h"
#include "Mario.h"

#define CAMERA_VELOCITY	0.025f

class CCamCheck
{
	bool available;
	int maxX;
	float x, vx;
	CMario* mario;
public:
	CCamCheck(int x, int maxX);
	void Update(DWORD dt);

	float GetX() { return x; }
	float GetMaxX() { return maxX; }
	bool IsAvalable() { return available; }
	void SetPlayer(CMario* mario) { this->mario = mario; }

};