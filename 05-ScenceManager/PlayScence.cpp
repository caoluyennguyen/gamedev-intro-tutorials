#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Ground.h"
#include "TileMap.h"
#include "Items.h"
#include "Venus.h"
#include "Pipe.h"
#include "EndPoint.h"
#include "HUD.h"
#include "MovingWood.h"
#include "BoomerangBro.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TILEMAP 1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_GRID	7

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_GROUND	4
#define OBJECT_TYPE_FIREBALL	5
#define OBJECT_TYPE_ITEM	6
#define OBJECT_TYPE_BREAKABLE_BRICK	7
#define OBJECT_TYPE_VENUS_RED	8
#define OBJECT_TYPE_VENUS_GREEN	9
#define OBJECT_TYPE_PIRANHA	10
#define OBJECT_TYPE_PIPE_NORMAL 11
#define OBJECT_TYPE_PIPE_GREEN_DOWN 12
#define OBJECT_TYPE_PIPE_GREEN_UP 13
#define OBJECT_TYPE_PIPE_BLACK_DOWN 14
#define OBJECT_TYPE_PIPE_BLACK_UP 15
#define OBJECT_TYPE_END_POINT 16
#define OBJECT_TYPE_RED_KOOPAS 17
#define OBJECT_TYPE_MOVING_WOOD 18
#define OBJECT_TYPE_BOOMERANG_BRO 19
#define OBJECT_TYPE_MULTI_BRICK 20
#define OBJECT_TYPE_CAM_CHECK 21

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024
#define DEATH_AREA 1000.0f

#define SCENE_INTRO_ID		1
#define SCENE_WORLDMAP_ID	2
#define SCENE_1_1_ID		3
#define SCENE_1_4_ID		4

void CPlayScene::_ParseSection_TILEMAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int pixel = atoi(tokens[0].c_str());
	wstring img_path = ToWSTR(tokens[1]);
	wstring file_path = ToWSTR(tokens[2]);
	int numCol = atoi(tokens[3].c_str());
	int numRow = atoi(tokens[4].c_str());
	int numColToRead = atoi(tokens[5].c_str());
	int numRowToRead = atoi(tokens[6].c_str());
	int idCell = atoi(tokens[7].c_str());
	mapWidth = atoi(tokens[8].c_str());
	minX = atoi(tokens[9].c_str());
	maxX = atoi(tokens[10].c_str());
	minY = atoi(tokens[11].c_str());
	maxY = atoi(tokens[12].c_str());

	//CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
	tileMap = new CTileMap(pixel, img_path.c_str(), file_path.c_str(), numCol, numRow, numColToRead, numRowToRead, idCell);
}

void CPlayScene::_ParseSection_GRID(string line)
{
	vector<string> tokens = split(line);

	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	LPCWSTR path = ToLPCWSTR(tokens[0]);

	grid = new CGrid(path, &objects);
}

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		//obj = CMario::GetInstance();
		obj = new CMario();
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA:
		{
			int state = atof(tokens[4].c_str());
			obj = new CGoomba(state);
			break;
		}
	case OBJECT_TYPE_BRICK:
		{
			int item_type = atof(tokens[4].c_str());
			obj = new CBrick(x, y, item_type);
			objects.push_back(((CBrick*)obj)->GetItem());
			break;
		}
	case OBJECT_TYPE_KOOPAS:
		{
			int state = atof(tokens[4].c_str());
			obj = new CKoopas(state);
			break;
		}
	case OBJECT_TYPE_PORTAL:
		{	
			float r = atof(tokens[4].c_str());
			float b = atof(tokens[5].c_str());
			int scene_id = atoi(tokens[6].c_str());
			obj = new CPortal(x, y, r, b, scene_id);
		}
		break;
	case OBJECT_TYPE_GROUND:
		{
			float r = atof(tokens[4].c_str());
			float b = atof(tokens[5].c_str());
			id = atoi(tokens[6].c_str());
			obj = new CGround(x, y, r, b, id);
		}
		break;
	case OBJECT_TYPE_ITEM:
		{
			id = atoi(tokens[4].c_str());
			obj = new CItems(id);
		}
		break;
	case OBJECT_TYPE_BREAKABLE_BRICK:
		{
			obj = new CBrick(x,y);
			obj->SetState(BRICK_STATE_BREAKABLE);
		}
		break;
	case OBJECT_TYPE_MULTI_BRICK:
		{
			int item_type = atof(tokens[4].c_str());
			obj = new CBrick(x, y, item_type);
			objects.push_back(((CBrick*)obj)->GetItem());
			obj->SetState(BRICK_STATE_MULTI_COIN);
		}
		break;
	case OBJECT_TYPE_VENUS_RED:
		{
			obj = new CVenus(VENUS_STATE_RED, y);
		}
		break;
	case OBJECT_TYPE_VENUS_GREEN:
		{
			obj = new CVenus(VENUS_STATE_GREEN_SHOOT, y);
		}
		break;
	case OBJECT_TYPE_PIRANHA:
		{
			obj = new CVenus(VENUS_STATE_PIRANHA_MOVE, y);
		}
		break;
	case OBJECT_TYPE_PIPE_NORMAL:
		{
			obj = new CPipe();
			obj->SetState(PIPE_STATE_NORMAL);
		}
		break;
	case OBJECT_TYPE_PIPE_GREEN_DOWN:
		{
			float posX = atof(tokens[4].c_str());
			float posY = atof(tokens[5].c_str());
			obj = new CPipe(posX, posY);
			obj->SetState(PIPE_STATE_SECRET_GREEN_DOWN);
		}
		break;
	case OBJECT_TYPE_PIPE_GREEN_UP:
		{
			obj = new CPipe();
			obj->SetState(PIPE_STATE_SECRET_GREEN_UP);
		}
		break;
	case OBJECT_TYPE_PIPE_BLACK_DOWN:
		{
			obj = new CPipe();
			obj->SetState(PIPE_STATE_SECRET_BLACK_DOWN);
		}
		break;
	case OBJECT_TYPE_PIPE_BLACK_UP:
		{
			float posX = atof(tokens[4].c_str());
			float posY = atof(tokens[5].c_str());
			obj = new CPipe(posX, posY);
			obj->SetState(PIPE_STATE_SECRET_BLACK_UP);
		}
		break;
	case OBJECT_TYPE_END_POINT:
		{
			obj = new CEndPoint();
		}
		break;
	case OBJECT_TYPE_RED_KOOPAS:
	{
		int state = atof(tokens[4].c_str());
		obj = new CKoopas(state, 1);
		break;
	}
	case OBJECT_TYPE_MOVING_WOOD:
	{
		obj = new CMovingWood();
		break;
	}
	case OBJECT_TYPE_BOOMERANG_BRO:
	{
		obj = new CBoomerangBro();
		objects.push_back(dynamic_cast<CBoomerangBro*>(obj)->fBoomerang);
		objects.push_back(dynamic_cast<CBoomerangBro*>(obj)->sBoomerang);
		break;
	}
	case OBJECT_TYPE_CAM_CHECK:
	{
		camCheck = new CCamCheck(atof(tokens[1].c_str()), atof(tokens[2].c_str()));
		camCheck->SetPlayer(player);
		return;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TILEMAP]") { section = SCENE_SECTION_TILEMAP; continue; }
		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[GRID]") {
			section = SCENE_SECTION_GRID; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TILEMAP: _ParseSection_TILEMAP(line); break;
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_GRID: _ParseSection_GRID(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"scenes\\textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	coObjects.clear();

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;
	else if (player->y > DEATH_AREA)
	{
		CGame::GetInstance()->SwitchScene(2);
		return;
	}

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	// turn on grid
	grid->GetListObject(&coObjects, cx, cy);
	coObjects.push_back(player);
	for (size_t i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Update(dt, &coObjects);
	}

	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	// turn off grid
	/*for (size_t i = 1; i < objects.size(); i++)
	{
		if (objects[i]->IsEnable()) coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}*/

	CGame *game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 3;

	if (cy < 0) cy = 0;
	if (cx < minX) cx = minX;
	else if (cx > maxX)
	{
		HUD::GetInstance()->SetEndScene(true);
		cx = maxX;
	} 
	
	if (camCheck != NULL && camCheck->IsAvalable())
	{
		camCheck->Update(dt);
		if (player->IsFlying())
		{
			CGame::GetInstance()->SetCamPos(int(camCheck->GetX()), int(cy));
		}
		else
			CGame::GetInstance()->SetCamPos(int(camCheck->GetX()), maxY);
	}
	else if (player->IsFlying())
	{
		CGame::GetInstance()->SetCamPos(int(cx), int(cy));
	}
	else if (player->GetState() != MARIO_STATE_DIE && !player->IsMoveEndScene())
	{
		if (player->y < minY)
		{
			cy = player->y - game->GetScreenHeight() / 2;
			if (cy < 0) cy = 0;
		}
		else cy = maxY;

		CGame::GetInstance()->SetCamPos(int(cx), int(cy));
	}
	//CGame::GetInstance()->SetCamPos(int(cx), int(cy));

	HUD::GetInstance()->Update(dt);
}

void CPlayScene::Render()
{
	// Render make CPU higher
	tileMap->Render(1);
	//player->Render();
	// turn off grid
	/*for (int i = 0; i < objects.size(); i++)
		if (objects[i]->IsEnable()) objects[i]->Render();*/

	// turn on grid
	for (int i = coObjects.size() - 1; i > -1; i--)
		coObjects[i]->Render();

	HUD::GetInstance()->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	if (grid) grid->Unload();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_F1:
		CGame::GetInstance()->SwitchScene(SCENE_INTRO_ID);
		break;
	case DIK_F2:
		CGame::GetInstance()->SwitchScene(SCENE_WORLDMAP_ID);
		break;
	case DIK_F3:
		CGame::GetInstance()->SwitchScene(SCENE_1_1_ID);
		break;
	case DIK_F4:
		CGame::GetInstance()->SwitchScene(SCENE_1_4_ID);
		break;
	}
	if (mario->GetState() == MARIO_STATE_DIE) return;

	switch (KeyCode)
	{
	case DIK_S:
		if (mario->IsAbleToJump() && !mario->IsFlying())
		{
			mario->SetState(MARIO_STATE_JUMP);
		}
		else if (mario->IsAbleToSlowFall() && !mario->IsFlying())
		{
			mario->SetIsSlowFall(true);
			mario->SetState(MARIO_STATE_SLOW_FALL);
		}
		if (mario->IsAbleToJumpHigh() && !mario->IsFlying() && mario->GetLevel() == MARIO_LEVEL_TAIL)
		{
			mario->StartFly();
		}
		if (mario->IsFlying())
		{
			mario->SetState(MARIO_STATE_FLY);
		}
		break;
	case DIK_R:
		mario->Reset();
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_TAIL);
		break;
	case DIK_4:
		mario->SetLevel(MARIO_LEVEL_FIRE);
		break;
	case DIK_A:
		// mario can run
		mario->SetAbleToRun(true);
		// mario can hold object
		mario->SetAbleToHoldObject(true);
		if (mario->GetLevel() == MARIO_LEVEL_FIRE || mario->GetLevel() == MARIO_LEVEL_TAIL)
		{
			if (mario->IsAbleToShoot())
			{
				//mario->StartShoot();
				mario->SetState(MARIO_STATE_HIT);
			}
		}
		break;
	case DIK_DOWN:
		if (mario->IsAbleToGoDownPipe())
			mario->SetState(MARIO_STATE_GO_DOWN_PIPE);
		else mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_UP:
		if (mario->IsAbleToGoUpPipe())
			mario->SetState(MARIO_STATE_GO_UP_PIPE);
		break;
	case DIK_I:
		mario->SetPosition(1212.0f, 390.0f);
		break;
	case DIK_O:
		mario->SetPosition(1710.0f, 369.0f);
		break;
	case DIK_P:
		mario->SetPosition(2260.0f, 76.0f);
		break;
	case DIK_J:
		mario->SetPosition(2106.0f, 564.0f);
		break;
	case DIK_K:
		mario->SetPosition(2498.0f, 300.0f);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if (mario->GetState() == MARIO_STATE_DIE) return;

	switch (KeyCode)
	{
	case DIK_RIGHT:
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetIsWalking(false);
		break;
	case DIK_LEFT:
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetIsWalking(false);
		break;
	case DIK_S:
		mario->SetAbleToJump(false);
		if (mario->IsAbleToSlowFall())
		{
			mario->SetIsSlowFall(false);
		}
		break;
	case DIK_A:
		mario->SetAbleToHoldObject(false);
		mario->SetAbleToRun(false);
		mario->SetAbleToJumpHigh(false);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_IDLE);
		break;
	/*case DIK_LSHIFT:
		break;*/
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	float vx, vy;
	mario->GetSpeed(vx, vy);

	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;

	if (game->IsKeyDown(DIK_RIGHT)) {
		if (mario->IsAbleToRun()) mario->SetState(MARIO_STATE_RUN_RIGHT);
		else mario->SetState(MARIO_STATE_WALKING_RIGHT);

		mario->SetIsWalking(true);
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		if (mario->IsAbleToRun()) mario->SetState(MARIO_STATE_RUN_LEFT);
		else mario->SetState(MARIO_STATE_WALKING_LEFT);

		mario->SetIsWalking(true);
	}
	else
	{
		if (mario->IsFlying() == false && mario->IsAbleToRun() == false)
		{
			HUD::GetInstance()->PowerDown();
		}
	}

	if (game->IsKeyDown(DIK_S)) {
		if (mario->IsAbleToJump()) mario->SetState(MARIO_STATE_JUMP);
	}
}