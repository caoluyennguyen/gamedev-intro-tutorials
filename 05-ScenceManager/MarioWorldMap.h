#pragma once
#include "GameObject.h"

#define MARIO_BBOX_WIDTH	16
#define MARIO_BBOX_HEIGHT	16

#define MARIO_VELOCITY	0.07f

class CMarioWorldMap : public CGameObject
{
	bool isMoving;
	int sceneId;
public:
	int moveLeft;
	int moveUp;
	int moveRight;
	int moveDown;

	CMarioWorldMap();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	float GetPositionX() { return this->x; };

	bool IsMoving() { return isMoving; }
	void SetMoving(bool moving) { this->isMoving = moving; }

	int GetSceneId() { return this->sceneId; }
	void SetSceneId(int id) { this->sceneId = id; }
};