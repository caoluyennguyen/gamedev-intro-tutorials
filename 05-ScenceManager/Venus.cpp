#include "Venus.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScence.h"

CVenus::CVenus(int state, int start_y) : CEnemy()
{
	this->start_y = start_y;

	isUp = true;

	direction = -1;

	startDisappear = 0;
	startShoot = 0;

	SetState(state);

	if (state != VENUS_STATE_PIRANHA_IDLE || state != VENUS_STATE_PIRANHA_MOVE)
	{
		fireball = new FireBall();
		fireball->SetState(FIREBALL_STATE_VENUS);
	}
}

void CVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == VENUS_STATE_DIE)
	{
		if (GetTickCount() - startDisappear > VENUS_DIE_TIME)
		{
			this->enable = false;
			return;
		}
	}

	CEnemy::Update(dt);
	if (fireball) fireball->Update(dt); // handle update ball when reach out screen

	y += dy;

	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->y < this->y) isUp = true;
	else isUp = false;
	
	if (mario->x > this->x) nx = 1;
	else nx = -1;

	if (isMoving)
	{
		if (y > start_y)
		{
			direction = -1;
			if (state == VENUS_STATE_RED) SetState(VENUS_STATE_RED_SHOOT);
			else if (state == VENUS_STATE_GREEN) SetState(VENUS_STATE_GREEN_SHOOT);
			else if (state == VENUS_STATE_PIRANHA_MOVE) SetState(VENUS_STATE_PIRANHA_IDLE);
		}
		else
		{
			if (state == VENUS_STATE_RED)
			{
				if (y < start_y - VENUS_BBOX_HEIGHT)
				{
					direction = 1;
					SetState(VENUS_STATE_RED_SHOOT);
					StartShoot();
				}
			}
			else
			{
				if (y < start_y - PIRANHA_BBOX_HEIGHT)
				{
					direction = 1;
					if (state == VENUS_STATE_GREEN)
					{
						SetState(VENUS_STATE_GREEN_SHOOT);
						StartShoot();
					}
					else if(state == VENUS_STATE_PIRANHA_MOVE)
					{
						SetState(VENUS_STATE_PIRANHA_IDLE);
					}
				}
			}
		}
			
	}
	else if (isShooting && GetTickCount() - startShoot > VENUS_SHOOT_TIME)
	{
		if (state == VENUS_STATE_RED_SHOOT)
		{
			SetState(VENUS_STATE_RED);
		}
		else if (state == VENUS_STATE_GREEN_SHOOT)
		{
			SetState(VENUS_STATE_GREEN);
		}
		else if(state == VENUS_STATE_PIRANHA_IDLE)
		{
			SetState(VENUS_STATE_PIRANHA_MOVE);
		}
	}
}

void CVenus::Render()
{
	int ani = VENUS_ANI_RED_UP_LEFT;

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
	else if (state == VENUS_STATE_DIE) ani = VENUS_ANI_DIE;
	else ani = VENUS_ANI_PIRANHA;
		

	animation_set->at(ani)->Render(x, y);

	CEnemy::Render();
	if (fireball) fireball->Render();
}

void CVenus::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case VENUS_STATE_RED:
		vy = direction * VENUS_MOVE_SPEED;
		isMoving = true;
		isShooting = false;
		break;
	case VENUS_STATE_RED_SHOOT:
		vy = 0;
		isMoving = false;
		isShooting = true;
		startShoot = GetTickCount();
		break;
	case VENUS_STATE_GREEN:
		vy = direction * VENUS_MOVE_SPEED;
		isMoving = true;
		isShooting = false;
		break;
	case VENUS_STATE_GREEN_SHOOT:
		vy = 0;
		isMoving = false;
		isShooting = true;
		startShoot = GetTickCount();
		break;
	case VENUS_STATE_PIRANHA_MOVE:
		vy = direction * VENUS_MOVE_SPEED;
		isMoving = true;
		isShooting = false;
		break;
	case VENUS_STATE_PIRANHA_IDLE:
		vy = 0;
		isMoving = false;
		isShooting = true;
		startShoot = GetTickCount();
		break;
	case VENUS_STATE_DIE:
		ScoreUp();
		startDisappear = GetTickCount();
		vx = vy = 0;
		break;
	}
}

void CVenus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == VENUS_STATE_DIE) return;
	left = x;
	top = y;

	if (state == VENUS_STATE_RED || state == VENUS_STATE_RED_SHOOT)
	{
		right = left + VENUS_BBOX_WIDTH;
		bottom = top + VENUS_BBOX_HEIGHT;
	}
	else
	{
		right = left + PIRANHA_BBOX_WIDTH;
		bottom = top + PIRANHA_BBOX_HEIGHT;
	}
}

void CVenus::StartShoot()
{
	fireball->SetPosition(this->x, this->y);
	if (isUp) fireball->SetSpeed(nx * 0.02f, -0.02f);
	else fireball->SetSpeed(nx * 0.02f, 0.02f);
}