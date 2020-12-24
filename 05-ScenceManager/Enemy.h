#pragma once
#include "GameObject.h"

class Enemy : public CGameObject
{
	int hp;
public:
	Enemy();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render() {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom) {};
	void SetState(int state) {};

	void LoseHp() { this->hp -= 1; }
};

