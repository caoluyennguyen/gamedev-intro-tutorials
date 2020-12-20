#pragma once
#include "GameObject.h"

#define BRICKPIECES_GRAVITY 0.0005f
#define BRICKPIECES_ANIM_SET 22
#define BRICKPIECES_ANIM_POS 3

class BrickPiece : public CGameObject
{
public:
	BrickPiece();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom) {};
};

typedef BrickPiece* LPBRICKPIECES;

class BrickPieces
{
	DWORD startTime = 0;
	vector<LPBRICKPIECES> pieces;

public:
	BrickPieces(float x, float y);
	~BrickPieces();

	void Update(DWORD dt);
	void Render();

	DWORD GetStartTimeRender() { return startTime; }
	void SetStartTimeRender(DWORD x) { startTime = x; }
};