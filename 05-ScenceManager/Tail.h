#pragma once
#include "GameObject.h"
#include "Effect.h"

#define TAIL_BBOX_WIDTH		10
#define TAIL_BBOX_HEIGHT	5

class Tail : public CGameObject
{
private:
	bool enable;
	CEffect* effect;
public:
	Tail();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	bool IsEnable() { return enable; }
	void SetEnable(bool enable) { this->enable = enable; }
	void SetNx(int nx) { this->nx = nx; }
};

