#pragma once
#include "Animations.h"

#define EFFECT_TYPE_SCORE	0

#define EFFECT_SCORE_ANI_SET	7

#define EFFECT_TIME_APPEAR	400

class CEffect
{
	float x, y;

	bool appear;
	LPANIMATION_SET ani_set;
	DWORD appear_start;
public:
	CEffect();
	void StartTimeAppear() { appear = true; appear_start = GetTickCount(); }
	void Update(DWORD dt);
	void Render();
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
};

