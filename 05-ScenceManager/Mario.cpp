#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
#include "Koopas.h"
#include "Ground.h"
#include "Items.h"
#include "Pipe.h"
#include "Venus.h"

CMario* CMario::__instance = NULL;

CMario* CMario::GetInstance()
{
	if (__instance == NULL) __instance = new CMario();
	return __instance;
}

CMario::CMario() : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	isAbleToJump = true;
	isAbleToHoldObject = false;
	isHoldObject = false;
	isAbleToRun = false;
	isAbleToJumpHigh = false;
	isAbleToShoot = false;
	countBall = 1;
	ani = -1;

	a = MARIO_ACCELERATION_WALK;

	/*start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y;*/ 

	fireball = new FireBall();
	tail = new Tail();

	/*for (int i = 0; i < 2; i++)
	{
		fireball = new FireBall();
		fireBalls.push_back(fireball);
	}*/
}

void CMario::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;

		// Check AABB collision
		LPGAMEOBJECT obj = coObjects->at(i);

		if (dynamic_cast<CKoopas*>(obj)) {
			float kLeft, kTop, kRight, kBottom;
			obj->GetBoundingBox(kLeft, kTop, kRight, kBottom);

			CKoopas* koopas = dynamic_cast<CKoopas*>(obj);
			if (CheckCollision(kLeft, kTop, kRight, kBottom)) {
				if (level == MARIO_LEVEL_TAIL && hitting == 1)
				{
					obj->SetState(KOOPAS_STATE_DIE_NGUA);
				}
				else if (isAbleToHoldObject)
				{
					isHoldObject = true;
					//int direction = (x - kLeft) < 0 ? 1 : -1;
					if (level > MARIO_LEVEL_SMALL)
					{
						obj->SetPosition(this->x + this->nx * 10.0f, this->y + 10.0f);
					}
					else {
						obj->SetPosition(this->x + this->nx * 10.0f, this->y);
					}
				}
				else {
					isHoldObject = false;
					if (obj->GetState() == KOOPAS_STATE_DIE)
					{
						StartShootingObject();
						obj->nx = this->nx;
						obj->SetState(KOOPAS_STATE_ROLLING);
					}
					else if (obj->GetState() == KOOPAS_STATE_DIE_NGUA)
					{
						StartShootingObject();
						obj->nx = this->nx;
						obj->SetState(KOOPAS_STATE_ROLLING_NGUA);
					}
				}
			}
		}
		
		else if (dynamic_cast<CGround*>(obj)) {
			CGround* ground = dynamic_cast<CGround*>(obj);

			if (ground->GetId() == GROUND_TYPE_NORMAL)
			{
				float kLeft, kTop, kRight, kBottom;
				obj->GetBoundingBox(kLeft, kTop, kRight, kBottom);

				if (CheckCollision(kLeft, kTop, kRight, kBottom) && kBottom > y) {
					y -= y + MARIO_BIG_BBOX_HEIGHT - kTop + 1.0f;
				}
			}
		}

		else if (dynamic_cast<CPipe*>(obj)) {
			float kLeft, kTop, kRight, kBottom;
			obj->GetBoundingBox(kLeft, kTop, kRight, kBottom);

			if (CheckCollision(kLeft, kTop, kRight, kBottom) && kBottom > y) {
				x -= 1.0f * nx;
			}
		}
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	// reset shooting timer if hitting time has passed
	if (GetTickCount() - shooting_start > MARIO_SHOOTING_TIME)
	{
		shooting_start = 0;
		shooting = 0;
	}
	// reset flying timer if hitting time has passed
	if (GetTickCount() - flying_start > MARIO_FLYING_TIME)
	{
		flying_start = 0;
		flying = false;
	}
	// reset hitting timer if hitting time has passed
	if (GetTickCount() - hitting_start > MARIO_HITTING_TIME)
	{
		hitting_start = 0;
		hitting = 0;
		this->tail->SetEnable(false);
	}
	// reset throwing timer if hitting time has passed
	if (GetTickCount() - throwing_start > MARIO_THROWING_TIME)
	{
		throwing_start = 0;
		throwing = 0;
	}
	// reset throwing timer if transform time has passed
	if (GetTickCount() - transform_start > MARIO_TRANSFORM_TIME)
	{
		transform_start = 0;
		isTransform = false;
	}

	// Calculate dx, dy 
	CGameObject::Update(dt);

	vy += MARIO_GRAVITY * dt;
	if (state == MARIO_STATE_DIE) {
		y += dy;
		return;
	}

	// Add acceleration
	if (state == MARIO_STATE_IDLE || state == MARIO_STATE_SIT || state == MARIO_STATE_HIT)
	{
		if (vx > MARIO_MIN_WALKING_SPEED) vx -= MARIO_ACCELERATION_WALK * dt;
		else if (vx < -MARIO_MIN_WALKING_SPEED) vx += MARIO_ACCELERATION_WALK * dt;
		else vx = 0;
	}
	else if (state == MARIO_STATE_WALKING_LEFT || state == MARIO_STATE_WALKING_RIGHT)
	{
		if (nx > 0)
		{
			if (vx < MARIO_MAX_WALKING_SPEED) {
				vx += MARIO_ACCELERATION_WALK * dt;
			}
			else vx = MARIO_MAX_WALKING_SPEED;
		}
		else {
			if (vx > -MARIO_MAX_WALKING_SPEED) {
				vx -= MARIO_ACCELERATION_WALK * dt;
			}
			else vx = -MARIO_MAX_WALKING_SPEED;
		}
	}
	else if (state == MARIO_STATE_RUN_RIGHT || state == MARIO_STATE_RUN_LEFT)
	{
		/*if (a < MARIO_ACCELERATION_RUN) a += 0.0001f * dt;
		else a = MARIO_ACCELERATION_RUN;*/
		if (nx > 0)
		{
			if (vx < MARIO_MAX_RUN_SPEED) {
				vx += MARIO_ACCELERATION_WALK * dt;
				isAbleToJumpHigh = false;
			}
			else isAbleToJumpHigh = true;
		}
		else {
			if (vx > -MARIO_MAX_RUN_SPEED) {
				vx -= MARIO_ACCELERATION_WALK * dt;
				isAbleToJumpHigh = false;
			}
			else isAbleToJumpHigh = true;
		}
	}
	if (state == MARIO_STATE_JUMP && isAbleToJump)
	{
		if (vy < 0) vy -= MARIO_ACCELERATION_JUMP * dt;
		else {
			if (level == MARIO_LEVEL_TAIL)
			{
				isAbleToSlowFall = true;
			}
			else isAbleToSlowFall = false;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);

	if (isTransform)
	{
		return;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0; 
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CKoopas *>(e->obj)) // if e->obj is Goomba 
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				x += dx;

				// jump on top >> kill Koopas and deflect a bit 
				if (e->ny < 0)
				{
					if (koopas->GetState() == KOOPAS_STATE_FLY)
					{
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						koopas->SetState(KOOPAS_STATE_WALKING);
						y += min_ty * dy + ny * 0.2f;
						koopas->ScoreUp();
					}
					else if (koopas->GetState() == KOOPAS_STATE_WALKING || koopas->GetState() == KOOPAS_STATE_ROLLING
						|| koopas->GetState() == KOOPAS_STATE_ROLLING_NGUA)
					{
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						koopas->SetState(KOOPAS_STATE_DIE);
						y += min_ty * dy + ny * 0.2f;
						koopas->ScoreUp();
					}
					/*else if (koopas->GetState() == KOOPAS_STATE_ROLLING_NGUA)
					{
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						koopas->SetState(KOOPAS_STATE_DIE_NGUA);
						y += min_ty * dy + ny * 0.2f;
					}*/
					else
					{
						y += dy;
					}
				}
				
				if (e->nx != 0 && !isAbleToHoldObject)
				{
					if (untouchable == 0 && hitting == 0)
					{
						if ((koopas->GetState() != KOOPAS_STATE_DIE && koopas->GetState() != KOOPAS_STATE_DIE_NGUA) ||
							(koopas->GetState() == KOOPAS_STATE_DIE && koopas->GetSpeedVx() != 0))
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else {
								SetState(MARIO_STATE_DIE);
							}
						}
						else
						{
							isHoldObject = false;
							if (koopas->GetState() == KOOPAS_STATE_DIE)
							{
								StartShootingObject();
								koopas->nx = this->nx;
								koopas->SetState(KOOPAS_STATE_ROLLING);
							}
							else if (koopas->GetState() == KOOPAS_STATE_DIE_NGUA)
							{
								StartShootingObject();
								koopas->nx = this->nx;
								koopas->SetState(KOOPAS_STATE_ROLLING_NGUA);
							}
						}
					}
				}
			}
			else if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() == GOOMBA_STATE_FLY)
					{
						goomba->SetState(GOOMBA_STATE_WALKING);
						goomba->ScoreUp();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else if (goomba->GetState() == GOOMBA_STATE_WALKING)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						goomba->ScoreUp();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else
					{
						if (state == MARIO_STATE_JUMP || state == MARIO_STATE_SLOW_FALL) SetState(MARIO_STATE_IDLE);
						isAbleToJump = true;
						vy = 0;
						y += min_ty * dy + ny * 0.2f;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
								StartTransform();
							}
							else 
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CBrick *>(e->obj))
			{
				if (e->obj->GetState() == BRICK_STATE_BREAK)
				{
					x += dx;
					y += dy;
				}
				else
				{
					x += min_tx * dx + nx * 0.2f;
					y += min_ty * dy + ny * 0.2f;

					CBrick* brick = dynamic_cast<CBrick*>(e->obj);

					if (e->nx != 0)
					{
						vx = 0;
					}

					if (e->ny < 0)
					{
						if (state == MARIO_STATE_JUMP || state == MARIO_STATE_SLOW_FALL) SetState(MARIO_STATE_IDLE);
						isAbleToJump = true;
						//isAbleToSlowFall = false;
						vy = 0;
					}
					else if (e->ny > 0)
					{
						vy += 0.1f;
						isAbleToJump = false;
						if (brick->GetState() == BRICK_STATE_AVAILABLE)
						{
							brick->SetState(BRICK_STATE_UNAVAILABLE);
						}
						else if (brick->GetState() == BRICK_STATE_BREAKABLE)
						{
							brick->SetState(BRICK_STATE_BREAK);
						}
					}
				}
			}
			else if (dynamic_cast<CGround*>(e->obj)) // if e->obj is Goomba 
			{
				CGround* ground = dynamic_cast<CGround*>(e->obj);

				if (e->nx != 0 && ground->GetId() == GROUND_TYPE_NORMAL)
				{
					x += min_tx * dx + nx * 0.2f;
					vx = 0;
				}
				else x += dx;

				if (e->ny < 0)
				{
					if (state == MARIO_STATE_JUMP || state == MARIO_STATE_SLOW_FALL) SetState(MARIO_STATE_IDLE);
					isAbleToJump = true;
					vy = 0;
					y += min_ty * dy + ny * 0.2f;
				}
				else if (e->ny > 0)
				{
					if (ground->GetId() == GROUND_TYPE_NORMAL) y += min_ty * dy + ny * 0.2f;
					else y += dy;
				}

			}
			else if (dynamic_cast<CPipe*>(e->obj)) // if e->obj is Goomba 
			{
				//CGround* ground = dynamic_cast<CGround*>(e->obj);

				if (e->nx != 0)
				{
					x += min_tx * dx + nx * 0.4f;
					vx = 0;
				}

				if (e->ny != 0)
				{
					if (state == MARIO_STATE_JUMP || state == MARIO_STATE_SLOW_FALL) SetState(MARIO_STATE_IDLE);
					isAbleToJump = true;
					vy = 0;
					y += min_ty * dy + ny * 0.2f;
				}
			}
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			else if (dynamic_cast<CItems *>(e->obj))
			{
				if (e->obj->GetState() == ITEM_TYPE_LEAF)
				{
					StartTransform();
					SetLevel(MARIO_LEVEL_TAIL);
					e->obj->SetEnable(false);
				}
				else if (e->obj->GetState() == ITEM_TYPE_RED_MUSROOM)
				{
					StartTransform();
					SetLevel(MARIO_LEVEL_BIG);
					e->obj->SetEnable(false);
				}
				else if (e->obj->GetState() == ITEM_TYPE_COIN)
				{
					x += dx;
					y += dy;
					e->obj->SetEnable(false);
				}
			}
			else if (dynamic_cast<CVenus *>(e->obj))
			{
				x += dx;
				y += dy;
				if (e->nx != 0 || e->ny != 0)
				{
					if (untouchable == 0)
					{
						if (level > MARIO_LEVEL_SMALL)
						{
							level = MARIO_LEVEL_SMALL;
							StartUntouchable();
						}
						else
							SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	/*for (int i = 0; i < 2; i++)
	{
		if (abs(fireBalls[i]->GetPositionX() - this->x) > 200) {
			fireBalls[i]->SetEnable(false);
			isAbleToShoot = true;
			fireBalls[i]->SetPosition(x, y);
			countBall++;
		}

		if (fireBalls[i]->IsEnable())
		{
			fireBalls[i]->Update(dt, coObjects);
		}
	}*/

	if (abs(fireball->GetPositionX() - this->x) > 200 || !fireball->IsEnable()) {
		fireball->SetEnable(false);
		isAbleToShoot = true;
	}

	if (fireball->IsEnable())
	{
		fireball->Update(dt, coObjects);
	}

	if (tail->IsEnable())
	{
		if (this->nx < 1)
		{
			tail->SetPosition(this->x - 10, this->y + 15);
		}
		else
		{
			tail->SetPosition(this->x + 20, this->y + 15);
		}
		tail->Update(dt, coObjects);
	}
}

void CMario::Render()
{
	if (state == MARIO_STATE_DIE) ani = MARIO_ANI_DIE;
	else
	{
		if (level == MARIO_LEVEL_BIG)
		{
			if (isTransform)
			{
				if (nx > 0) ani = MARIO_ANI_SMALL_TRANSFORM_RIGHT;
				else ani = MARIO_ANI_SMALL_TRANSFORM_LEFT;
			}
			else if (state == MARIO_STATE_JUMP)
			{
				if (nx > 0) {
					// check if mario can fly
					if (isAbleToJumpHigh && isAbleToRun) ani = MARIO_ANI_BIG_FLY_RIGHT;
					else {
						if (vy < 0) ani = MARIO_ANI_BIG_JUMP_UP_RIGHT;
						else ani = MARIO_ANI_BIG_JUMP_DOWN_RIGHT;
					}
				}
				else {
					if (isAbleToJumpHigh && isAbleToRun) ani = MARIO_ANI_BIG_FLY_LEFT;
					else {
						if (vy < 0) ani = MARIO_ANI_BIG_JUMP_UP_LEFT;
						else ani = MARIO_ANI_BIG_JUMP_DOWN_LEFT;
					}
				}
			}
			else {
				if (state == MARIO_STATE_SIT)
				{
					if (nx > 0) ani = MARIO_ANI_BIG_SIT_RIGHT;
					else ani = MARIO_ANI_BIG_SIT_LEFT;
				}
				else {
					if (vx == 0)
					{
						if (vy != 0 && !isAbleToJump)
						{
							if (nx > 0) {
								if (vy < 0) ani = MARIO_ANI_BIG_JUMP_UP_RIGHT;
								else ani = MARIO_ANI_BIG_JUMP_DOWN_RIGHT;
							}
							else {
								if (vy < 0) ani = MARIO_ANI_BIG_JUMP_UP_LEFT;
								else ani = MARIO_ANI_BIG_JUMP_DOWN_LEFT;
							}
						}
						else
						{
							if (isHoldObject)
							{
								if (nx > 0) ani = MARIO_ANI_BIG_IDLE_HOLD_RIGHT;
								else ani = MARIO_ANI_BIG_IDLE_HOLD_LEFT;
							}
							else {
								if (nx > 0) {
									if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_BIG_JUMP_DOWN_RIGHT;
									else ani = MARIO_ANI_BIG_IDLE_RIGHT;
								}

								else {
									if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_BIG_JUMP_DOWN_LEFT;
									ani = MARIO_ANI_BIG_IDLE_LEFT;
								}
							}
						}
					}
					else
					{
						if (isHoldObject)
						{
							if (nx > 0) {
								ani = MARIO_ANI_BIG_WALK_HOLD_RIGHT;
							}
							else {
								ani = MARIO_ANI_BIG_WALK_HOLD_LEFT;
							}
						}
						else if (shooting == 1)
						{
							if (nx > 0) {
								ani = MARIO_ANI_BIG_HIT_RIGHT;
							}
							else {
								ani = MARIO_ANI_BIG_HIT_LEFT;
							}
						}
						else {
							if (vy != 0 && !isAbleToJump)
							{
								if (nx > 0) {
									if (vy < 0) ani = MARIO_ANI_BIG_JUMP_UP_RIGHT;
									else ani = MARIO_ANI_BIG_JUMP_DOWN_RIGHT;
								}
								else {
									if (vy < 0) ani = MARIO_ANI_BIG_JUMP_UP_LEFT;
									else ani = MARIO_ANI_BIG_JUMP_DOWN_LEFT;
								}
							}
							else {
								if (nx > 0) {
									if (vx < 0)
									{
										ani = MARIO_ANI_BIG_STOP_LEFT;
									}
									else {
										if (state == MARIO_STATE_RUN_RIGHT)
										{
											if (vx < MARIO_MAX_WALKING_SPEED) ani = MARIO_ANI_BIG_WALKING_RIGHT;
											else if (vx < MARIO_MAX_RUN_SPEED) ani = MARIO_ANI_BIG_RUN_RIGHT;
											else ani = MARIO_ANI_BIG_SWIFT_RIGHT;
										}
										else {
											if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_BIG_JUMP_DOWN_RIGHT;
											else ani = MARIO_ANI_BIG_WALKING_RIGHT;
										}
									}
								}
								else {
									if (vx > 0)
									{
										ani = MARIO_ANI_BIG_STOP_RIGHT;
									}
									else {
										if (state == MARIO_STATE_RUN_LEFT)
										{
											if (vx > -MARIO_MAX_WALKING_SPEED) ani = MARIO_ANI_BIG_WALKING_LEFT;
											else if (vx > -MARIO_MAX_RUN_SPEED) ani = MARIO_ANI_BIG_RUN_LEFT;
											else ani = MARIO_ANI_BIG_SWIFT_LEFT;
										}
										else {
											if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_BIG_JUMP_DOWN_LEFT;
											else ani = MARIO_ANI_BIG_WALKING_LEFT;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (isTransform)
			{
				if (nx > 0) ani = MARIO_ANI_SMALL_TRANSFORM_RIGHT;
				else ani = MARIO_ANI_SMALL_TRANSFORM_LEFT;
			}
			else if (state == MARIO_STATE_JUMP)
			{
				if (nx > 0) {
					if (isAbleToJumpHigh && isAbleToRun) ani = MARIO_ANI_SMALL_FLY_RIGHT;
					else ani = MARIO_ANI_SMALL_JUMP_RIGHT;
				}
				else {
					if (isAbleToJumpHigh && isAbleToRun) ani = MARIO_ANI_SMALL_FLY_LEFT;
					else ani = MARIO_ANI_SMALL_JUMP_LEFT;
				}
			}
			else {
				if (vx == 0)
				{
					if (vy != 0 && !isAbleToJump)
					{
						if (nx > 0) ani = MARIO_ANI_SMALL_JUMP_RIGHT;
						else ani = MARIO_ANI_SMALL_JUMP_LEFT;
					}
					else
					{
						if (isHoldObject)
						{
							if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_HOLD_RIGHT;
							else ani = MARIO_ANI_SMALL_IDLE_HOLD_LEFT;
						}
						else {
							if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
							else ani = MARIO_ANI_SMALL_IDLE_LEFT;
						}
					}
				}
				else
				{
					if (isHoldObject)
					{
						if (nx > 0) {
							ani = MARIO_ANI_SMALL_WALK_HOLD_RIGHT;
						}
						else {
							ani = MARIO_ANI_SMALL_WALK_HOLD_LEFT;
						}
					}
					else if (shooting == 1)
					{
						if (nx > 0) {
							ani = MARIO_ANI_SMALL_HIT_RIGHT;
						}
						else {
							ani = MARIO_ANI_SMALL_HIT_LEFT;
						}
					}
					else {
						if (vy != 0 && !isAbleToJump)
						{
							if (nx > 0) ani = MARIO_ANI_SMALL_JUMP_RIGHT;
							else ani = MARIO_ANI_SMALL_JUMP_LEFT;
						}
						else {
							if (nx > 0) {
								if (vx < 0)
								{
									ani = MARIO_ANI_SMALL_STOP_LEFT;
								}
								else {
									if (state == MARIO_STATE_RUN_RIGHT)
									{
										if (vx < MARIO_MAX_WALKING_SPEED) ani = MARIO_ANI_SMALL_WALKING_RIGHT;
										else if (vx < MARIO_MAX_RUN_SPEED) ani = MARIO_ANI_SMALL_RUN_RIGHT;
										else ani = MARIO_ANI_SMALL_SWIFT_RIGHT;
									}
									else ani = MARIO_ANI_SMALL_WALKING_RIGHT;
								}
							}
							else {
								if (vx > 0)
								{
									ani = MARIO_ANI_SMALL_STOP_RIGHT;
								}
								else {
									if (state == MARIO_STATE_RUN_LEFT)
									{
										if (vx > -MARIO_MAX_WALKING_SPEED) ani = MARIO_ANI_SMALL_WALKING_LEFT;
										else if (vx > -MARIO_MAX_RUN_SPEED) ani = MARIO_ANI_SMALL_RUN_LEFT;
										else ani = MARIO_ANI_SMALL_SWIFT_LEFT;
									}
									else ani = MARIO_ANI_SMALL_WALKING_LEFT;
								}
							}
						}
					}
				}
			}
		}
		else if (level == MARIO_LEVEL_TAIL)
		{
			if (isTransform)
			{
				ani = MARIO_ANI_BIG_TRANSFORM;
			}
			else if (state == MARIO_STATE_JUMP)
			{
				if (nx > 0) {
					if (isAbleToJumpHigh && isAbleToRun) ani = MARIO_ANI_TAIL_JUMP_HIGH_RIGHT;
					else {
						if (vy < 0) ani = MARIO_ANI_TAIL_JUMP_UP_RIGHT;
						else ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;
					}
				}
				else {
					if (isAbleToJumpHigh && isAbleToRun) ani = MARIO_ANI_TAIL_JUMP_HIGH_LEFT;
					else {
						if (vy < 0) ani = MARIO_ANI_TAIL_JUMP_UP_LEFT;
						else ani = MARIO_ANI_TAIL_JUMP_DOWN_LEFT;
					}
					
				}
			}
			else if (state == MARIO_STATE_SLOW_FALL)
			{
				if (!isAbleToJump)
				{
					if (vy < MARIO_MIN_JUMP_SPEED)
					{
						if (nx > 0)
						{
							ani = MARIO_ANI_TAIL_SLOW_FALL_RIGHT ;
						}
						else ani = MARIO_ANI_TAIL_SLOW_FALL_LEFT;
					}
					else {
						if (nx > 0)
						{
							ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;
						}
						else ani = MARIO_ANI_TAIL_JUMP_DOWN_LEFT;
					}
				}
				else
				{
					if (nx > 0)
					{
						ani = MARIO_ANI_TAIL_IDLE_RIGHT;
					}
					else ani = MARIO_ANI_TAIL_IDLE_LEFT;
				}
			}
			else if (state == MARIO_STATE_FLY)
			{
				if (vy < 0)
				{
					if (nx > 0)
					{
						ani = MARIO_ANI_TAIL_FLY_RIGHT;
					}
					else ani = MARIO_ANI_TAIL_FLY_LEFT;
				}
				else {
					if (nx > 0)
					{
						ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;
					}
					else ani = MARIO_ANI_TAIL_JUMP_DOWN_LEFT;
				}
			}
			else if (state == MARIO_STATE_HIT)
			{
				if (nx > 0)  {
					if (hitting == 1) ani = MARIO_ANI_TAIL_HIT_TAIL_RIGHT;
					else ani = MARIO_ANI_TAIL_IDLE_RIGHT;
				}			
				else {
					if (hitting == 1) ani = MARIO_ANI_TAIL_HIT_TAIL_LEFT;
					else ani = MARIO_ANI_TAIL_IDLE_LEFT;
				}
				
				if (this->tail->IsEnable())
				{
					this->tail->Render();
				}
			}
			else {
				if (state == MARIO_STATE_SIT)
				{
					if (nx > 0) ani = MARIO_ANI_TAIL_SIT_RIGHT;
					else ani = MARIO_ANI_TAIL_SIT_LEFT;
				}
				else {
					if (vx == 0)
					{
						if (vy != 0 && !isAbleToJump)
						{
							if (nx > 0) {
								if (vy < 0) ani = MARIO_ANI_TAIL_JUMP_UP_RIGHT;
								else ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;
							}
							else {
								if (vy < 0) ani = MARIO_ANI_TAIL_JUMP_UP_LEFT;
								else ani = MARIO_ANI_TAIL_JUMP_DOWN_LEFT;
							}
						}
						else
						{
							if (isHoldObject)
							{
								if (nx > 0) ani = MARIO_ANI_TAIL_IDLE_HOLD_RIGHT;
								else ani = MARIO_ANI_TAIL_IDLE_HOLD_LEFT;
							}
							else {
								if (nx > 0) {
									if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;
									else ani = MARIO_ANI_TAIL_IDLE_RIGHT;
								}

								else {
									if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_TAIL_JUMP_DOWN_LEFT;
									else ani = MARIO_ANI_TAIL_IDLE_LEFT;
								}
							}
						}
					}
					else
					{
						if (isHoldObject)
						{
							if (nx > 0) {
								ani = MARIO_ANI_TAIL_WALK_HOLD_RIGHT;
							}
							else {
								ani = MARIO_ANI_TAIL_WALK_HOLD_LEFT;
							}
						}
						else if (shooting == 1)
						{
							if (nx > 0) {
								ani = MARIO_ANI_TAIL_HIT_RIGHT;
							}
							else {
								ani = MARIO_ANI_TAIL_HIT_LEFT;
							}
						}
						else {
							if (vy != 0 && !isAbleToJump)
							{
								if (nx > 0) {
									if (vy < 0)
									{
										if (flying) ani = MARIO_ANI_TAIL_FLY_RIGHT;
										else ani = MARIO_ANI_TAIL_JUMP_UP_RIGHT;
									}
									else {
										if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;
										else ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;
										//else ani = MARIO_ANI_TAIL_FLY_RIGHT;

										/*if (vy < MARIO_MIN_JUMP_SPEED && flying == 1) ani = MARIO_ANI_TAIL_FLY_RIGHT;
										else ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;*/
									}
										
								}
								else {
									if (vy < 0) {
										if (flying) ani = MARIO_ANI_TAIL_FLY_LEFT;
										else ani = MARIO_ANI_TAIL_JUMP_UP_LEFT;
									}
									else {
										if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_TAIL_JUMP_DOWN_LEFT;
										else ani = MARIO_ANI_TAIL_JUMP_DOWN_LEFT;
										//else ani = MARIO_ANI_TAIL_FLY_LEFT;

										/*if (vy < MARIO_MIN_JUMP_SPEED && flying == 1) ani = MARIO_ANI_TAIL_FLY_LEFT;
										else ani = MARIO_ANI_TAIL_JUMP_DOWN_LEFT;*/
									}
								}
							}
							else {
								if (nx > 0) {
									if (vx < 0)
									{
										ani = MARIO_ANI_TAIL_STOP_LEFT;
									}
									else {
										if (hitting == 1)
										{
											ani == MARIO_ANI_TAIL_HIT_TAIL_RIGHT;
										}
										else
										{
											if (state == MARIO_STATE_RUN_RIGHT)
											{
												if (vx < MARIO_MAX_WALKING_SPEED) ani = MARIO_ANI_TAIL_WALKING_RIGHT;
												else if (vx < MARIO_MAX_RUN_SPEED) ani = MARIO_ANI_TAIL_RUN_RIGHT;
												else ani = MARIO_ANI_TAIL_SWIFT_RIGHT;
											}
											else {
												if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;
												else ani = MARIO_ANI_TAIL_WALKING_RIGHT;
											}
										}
									}
								}
								else {
									if (vx > 0)
									{
										ani = MARIO_ANI_TAIL_STOP_RIGHT;
									}
									else {
										if (hitting == 1)
										{
											ani == MARIO_ANI_TAIL_HIT_TAIL_LEFT;
										}
										else
										{
											if (state == MARIO_STATE_RUN_LEFT)
											{
												if (vx > -MARIO_MAX_WALKING_SPEED) ani = MARIO_ANI_TAIL_WALKING_LEFT;
												else if (vx > -MARIO_MAX_RUN_SPEED) ani = MARIO_ANI_TAIL_RUN_LEFT;
												else ani = MARIO_ANI_TAIL_SWIFT_LEFT;
											}
											else {
												if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_TAIL_JUMP_DOWN_LEFT;
												else ani = MARIO_ANI_TAIL_WALKING_LEFT;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else if (level == MARIO_LEVEL_FIRE)
		{
			if (state == MARIO_STATE_JUMP)
			{
				if (nx > 0) {
					if (isAbleToJumpHigh && isAbleToRun) ani = MARIO_ANI_FIRE_FLY_RIGHT;
					else {
						if (vy < 0) ani = MARIO_ANI_FIRE_JUMP_UP_RIGHT;
						else ani = MARIO_ANI_FIRE_JUMP_DOWN_RIGHT;
					}
				}
				else {
					if (isAbleToJumpHigh && isAbleToRun) ani = MARIO_ANI_FIRE_FLY_LEFT;
					else {
						if (vy < 0) ani = MARIO_ANI_FIRE_JUMP_UP_LEFT;
						else ani = MARIO_ANI_FIRE_JUMP_DOWN_LEFT;
					}
				}
			}
			else if (state == MARIO_STATE_HIT)
			{
				if (nx > 0) {
					if (throwing == 1) ani = MARIO_ANI_FIRE_THROW_BALL_RIGHT;
					else ani = MARIO_ANI_FIRE_IDLE_RIGHT;
				}

				else {
					if (throwing == 1) ani = MARIO_ANI_FIRE_THROW_BALL_LEFT;
					else ani = MARIO_ANI_FIRE_IDLE_LEFT;
				}
			}
			else {
				if (state == MARIO_STATE_SIT)
				{
					if (nx > 0) ani = MARIO_ANI_FIRE_SIT_RIGHT;
					else ani = MARIO_ANI_FIRE_SIT_LEFT;
				}
				else {
					if (vx == 0)
					{
						if (vy != 0 && !isAbleToJump)
						{
							if (nx > 0) {
								if (vy < 0) ani = MARIO_ANI_FIRE_JUMP_UP_RIGHT;
								else ani = MARIO_ANI_FIRE_JUMP_DOWN_RIGHT;
							}
							else {
								if (vy < 0) ani = MARIO_ANI_FIRE_JUMP_UP_LEFT;
								else ani = MARIO_ANI_FIRE_JUMP_DOWN_LEFT;
							}
						}
						else
						{
							if (isHoldObject)
							{
								if (nx > 0) ani = MARIO_ANI_FIRE_IDLE_HOLD_RIGHT;
								else ani = MARIO_ANI_FIRE_IDLE_HOLD_LEFT;
							}
							else {
								if (nx > 0) {
									if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_FIRE_JUMP_DOWN_RIGHT;
									else ani = ani = MARIO_ANI_FIRE_IDLE_RIGHT;
								}

								else {
									if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_FIRE_JUMP_DOWN_LEFT;
									else ani = MARIO_ANI_FIRE_IDLE_LEFT;
								}
							}
						}
					}
					else
					{
						if (isHoldObject)
						{
							if (nx > 0) {
								ani = MARIO_ANI_FIRE_WALK_HOLD_RIGHT;
							}
							else {
								ani = MARIO_ANI_FIRE_WALK_HOLD_LEFT;
							}
						}
						else if (shooting == 1)
						{
							if (nx > 0) {
								ani = MARIO_ANI_FIRE_HIT_RIGHT;
							}
							else {
								ani = MARIO_ANI_FIRE_HIT_LEFT;
							}
						}
						else {
							if (vy != 0 && !isAbleToJump)
							{
								if (nx > 0) {
									if (vy < 0) ani = MARIO_ANI_FIRE_JUMP_UP_RIGHT;
									else ani = MARIO_ANI_FIRE_JUMP_DOWN_RIGHT;
								}
								else {
									if (vy < 0) ani = MARIO_ANI_FIRE_JUMP_UP_LEFT;
									else ani = MARIO_ANI_FIRE_JUMP_DOWN_LEFT;
								}
							}
							else {
								if (nx > 0) {
									if (vx < 0)
									{
										ani = MARIO_ANI_FIRE_STOP_LEFT;
									}
									else {
										if (state == MARIO_STATE_RUN_RIGHT)
										{
											if (vx < MARIO_MAX_WALKING_SPEED) ani = MARIO_ANI_FIRE_WALKING_RIGHT;
											else if (vx < MARIO_MAX_RUN_SPEED) ani = MARIO_ANI_FIRE_RUN_RIGHT;
											else ani = MARIO_ANI_FIRE_SWIFT_RIGHT;
										}
										else {
											if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_FIRE_JUMP_DOWN_RIGHT;
											else ani = MARIO_ANI_FIRE_WALKING_RIGHT;
										}
									}
								}
								else {
									if (vx > 0)
									{
										ani = MARIO_ANI_FIRE_STOP_RIGHT;
									}
									else {
										if (state == MARIO_STATE_RUN_LEFT)
										{
											if (vx > -MARIO_MAX_WALKING_SPEED) ani = MARIO_ANI_FIRE_WALKING_LEFT;
											else if (vx > -MARIO_MAX_RUN_SPEED) ani = MARIO_ANI_FIRE_RUN_LEFT;
											else ani = MARIO_ANI_FIRE_SWIFT_LEFT;
										}
										else
										{
											if (vy > MARIO_MIN_JUMP_SPEED) ani = MARIO_ANI_FIRE_JUMP_DOWN_LEFT;
											else ani = MARIO_ANI_FIRE_WALKING_LEFT;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	if (fireball->IsEnable())
	{
		fireball->Render();
	}
	
	/*for (int i = 0; i < 2; i++)
	{
		if (fireBalls[i]->IsEnable())
			fireBalls[i]->Render();
	}*/

	int alpha = 255;
	if (untouchable) alpha = 128;

	// Error render Mario hit
	
	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		if (vy == 0) {
			// mario can fly when can run and jump high
			if (isAbleToJumpHigh && level != MARIO_LEVEL_TAIL)
			{
				vy = -MARIO_JUMP_HIGH_SPEED;
			}
			else
				vy = -MARIO_JUMP_SPEED;
		}
		break; 
	case MARIO_STATE_IDLE:
		break;
	case MARIO_STATE_DIE:
		vx = 0;
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_SIT:
		vy = 0;
		break;
	case MARIO_STATE_RUN_RIGHT:
		nx = 1;
		break;
	case MARIO_STATE_RUN_LEFT:
		nx = -1;
		break;
	case MARIO_STATE_FLY:
		vy = -0.1f;
		break;
	case MARIO_STATE_SLOW_FALL:
		vy = 0.01f;
		break;
	case MARIO_STATE_HIT:
		if (level == MARIO_LEVEL_TAIL)
		{
			this->tail->SetEnable(true);
			this->tail->SetNx(nx);
			StartHittingObject();
		}
		else StartThrowingObject();
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_FIRE)
	{
		if (state == MARIO_STATE_SIT)
		{
			right = x + MARIO_SIT_BBOX_WIDTH;
			bottom = y + MARIO_SIT_BBOX_HEIGHT;
		}
		else {
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_TAIL)
	{
		if (state == MARIO_STATE_SIT)
		{
			right = x + MARIO_SIT_BBOX_WIDTH;
			bottom = y + MARIO_SIT_BBOX_HEIGHT;
		}
		else {
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CMario::Clear()
{
	for (int i = 0; i < 2; i++)
	{
		delete fireBalls[i];
	}
	fireBalls.clear();
}

void CMario::StartShoot()
{
	fireball->SetEnable(true);
	fireball->SetPosition(this->x, this->y);
	fireball->nx = this->nx;
	isAbleToShoot = false;
	/*if (countBall > 0)
	{
		fireBalls[countBall]->SetEnable(true);
		fireBalls[countBall]->SetPosition(this->x, this->y);
		fireBalls[countBall]->nx = this->nx;
	}
	countBall--;
	if (countBall < 0) isAbleToShoot = false;*/
}

void CMario::SetLevel(int l)
{
	level = l;
	if (l == MARIO_LEVEL_FIRE) isAbleToShoot = true;
	else isAbleToShoot = false;
}