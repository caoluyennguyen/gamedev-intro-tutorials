#pragma once
#include "Animations.h"

#define EFFECT_TYPE_SCORE_100	0
#define EFFECT_TYPE_TRANSFORM	1
#define EFFECT_TYPE_SCORE_1000	2

#define EFFECT_SCORE_ANI_SET	7

#define EFFECT_TIME_APPEAR	400
#define EFFECT_VELOCITY	-0.1f

class CEffect
{
	float x, y;

	bool appear;
	int state;
	LPANIMATION_SET ani_set;
	DWORD appear_start;
public:
	CEffect();
	void StartTimeAppear() { appear = true; appear_start = GetTickCount(); }
	void Update(DWORD dt);
	void Render();
	void RenderOneTime();
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetState(int state);
};

