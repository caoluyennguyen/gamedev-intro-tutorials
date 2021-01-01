#pragma once
#include "GameObject.h"

class CTurtle : public CGameObject
{
	int startX;
public:
	CTurtle();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state) { this->state = state; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
};

