#include "BrickPiece.h"
#include "Animations.h"

BrickPiece::BrickPiece()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(BRICKPIECES_ANIM_SET));
}

void BrickPiece::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	CGameObject::Update(dt);
	vy += BRICKPIECES_GRAVITY * dt;

	x += dx;
	y += dy;
}

void BrickPiece::Render()
{
	animation_set->at(BRICKPIECES_ANIM_POS)->Render(x, y);
}

BrickPieces::BrickPieces(float x, float y)
{
	BrickPiece* piece;

	for (int i = 1; i <= 4; i++)
	{
		piece = new BrickPiece();
		piece->SetPosition(x, y);
		pieces.push_back(piece);
	}

	pieces.at(0)->SetSpeed(-0.02f, -0.15f);
	pieces.at(1)->SetSpeed(-0.02f, -0.1f);
	pieces.at(2)->SetSpeed(0.02f, -0.15f);
	pieces.at(3)->SetSpeed(0.02f, -0.1f);
}

BrickPieces::~BrickPieces()
{
	for (int i = 0; i < 4; i++)
		delete(pieces[i]);

	pieces.clear();
}

void BrickPieces::Update(DWORD dt)
{
	for (LPBRICKPIECES piece : pieces)
		piece->Update(dt);
}

void BrickPieces::Render()
{
	for (LPBRICKPIECES piece : pieces)
		piece->Render();
}