#pragma once
#include "Animations.h"
#include "GameObject.h"

#define CHECKPOINT_BBOX_WIDTH	16
#define CHECKPOINT_BBOX_HEIGHT	16

#define CHECKPOINT_STATE_NORMAL	0
#define CHECKPOINT_STATE_START	1

class CCheckPoint : public CGameObject
{
	bool isActive;
	int sceneId;
public:
	int left, right, bottom, top;

	CCheckPoint() {};
	CCheckPoint(int left = 0, int top = 0, int right = 1, int bottom = 0, int sceneId = 0);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	void GetDirection(int& l, int& t, int& r, int& b) { l = left; t = top; r = right; b = bottom; };

	int GetSceneId() { return this->sceneId; }
	void SetSceneId(int id) { this->sceneId = id; }
};
