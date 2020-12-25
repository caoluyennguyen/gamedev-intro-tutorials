#include "Enemy.h"

CEnemy::CEnemy() : CGameObject()
{
	effect = new CEffect();
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);
	effect->Update(dt);
}

void CEnemy::Render()
{
	RenderBoundingBox();
	effect->Render();
}

void CEnemy::ScoreUp()
{
	effect->SetPosition(this->x, this->y);
	effect->StartTimeAppear();
}