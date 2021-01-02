#pragma once
#include "GameObject.h"
#include "Effect.h"

#define ENDPOINT_STATE_EMPTY	0
#define ENDPOINT_STATE_STAR		1
#define ENDPOINT_STATE_FLOWER	2
#define ENDPOINT_STATE_MUSROOM	3

#define ENDPOINT_BBOX_WIDTH		26
#define ENDPOINT_BBOX_HEIGHT	26

#define ROLLING_DEFAULT_TIME	100

class CEndPoint : public CGameObject
{
	CEffect* effect;
	DWORD rolling_start;
	DWORD switch_scene_start;
public:
	CEndPoint();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartRolling() { rolling_start = GetTickCount(); }
	void StartEffect();
	void StartSwitchScene();
};
