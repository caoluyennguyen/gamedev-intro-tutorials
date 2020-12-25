#include "Venus.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScence.h"

CVenus::CVenus(int state) : CEnemy()
{
	start_x = x;
	start_y = y;

	isUp = true;

	SetState(state);
}

void CVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt);

	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void CVenus::Render()
{
	int ani = VENUS_ANI_RED_DOWN_LEFT;

	if (state == VENUS_STATE_RED) {
		if (isUp)
		{
			if (nx > 0) ani = VENUS_ANI_RED_UP_RIGHT;
			else ani = VENUS_ANI_RED_UP_LEFT;
		}
		else
		{
			if (nx > 0) ani = VENUS_ANI_RED_DOWN_RIGHT;
			else ani = VENUS_ANI_RED_DOWN_LEFT;
		}
	}
	else if (state == VENUS_STATE_RED_SHOOT) {
		if (isUp)
		{
			if (nx > 0) ani = VENUS_ANI_RED_SHOOT_UP_RIGHT;
			else ani = VENUS_ANI_RED_SHOOT_UP_LEFT;
		}
		else
		{
			if (nx > 0) ani = VENUS_ANI_RED_SHOOT_DOWN_RIGHT;
			else ani = VENUS_ANI_RED_SHOOT_DOWN_LEFT;
		}
	}
	else if (state == VENUS_STATE_GREEN) {
		if (isUp)
		{
			if (nx > 0) ani = VENUS_ANI_GREEN_UP_RIGHT;
			else ani = VENUS_ANI_GREEN_UP_LEFT;
		}
		else
		{
			if (nx > 0) ani = VENUS_ANI_GREEN_DOWN_RIGHT;
			else ani = VENUS_ANI_GREEN_DOWN_LEFT;
		}
	}
	else if (state == VENUS_STATE_GREEN_SHOOT) {
		if (isUp)
		{
			if (nx > 0) ani = VENUS_ANI_GREEN_SHOOT_UP_RIGHT;
			else ani = VENUS_ANI_GREEN_SHOOT_UP_LEFT;
		}
		else
		{
			if (nx > 0) ani = VENUS_ANI_GREEN_SHOOT_DOWN_RIGHT;
			else ani = VENUS_ANI_GREEN_SHOOT_DOWN_LEFT;
		}
	}
	else ani = VENUS_ANI_PIRANHA;

	animation_set->at(ani)->Render(x, y);

	CEnemy::Render();
}

void CVenus::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case VENUS_STATE_RED:
		vx = 0;
		vy = 0;
		break;
	case VENUS_STATE_GREEN:
		vx = 0;
		vy = 0;
		break;
	}
}