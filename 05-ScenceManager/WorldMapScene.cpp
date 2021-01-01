#include <iostream>
#include <fstream>

#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Ground.h"
#include "TileMap.h"
#include "WorldMapScene.h"
#include "CheckPoint.h"
#include "Grass.h"

using namespace std;

CWorldMapScene::CWorldMapScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CWorldMapSceneKeyHandler(this);
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

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_CHECKPOINT	1
#define OBJECT_TYPE_GRASS	2
#define OBJECT_TYPE_CASTLE	3
#define OBJECT_TYPE_START	4

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


void CWorldMapScene::_ParseSection_TILEMAP(string line)
{
	//vector<string> tokens = split(line);

	//if (tokens.size() < 5) return; // skip invalid lines

	//int pixel = atoi(tokens[0].c_str());
	//wstring img_path = ToWSTR(tokens[1]);
	//wstring file_path = ToWSTR(tokens[2]);
	//int numCol = atoi(tokens[3].c_str());
	//int numRow = atoi(tokens[4].c_str());
	//int numColToRead = atoi(tokens[5].c_str());
	//int numRowToRead = atoi(tokens[6].c_str());
	//int idCell = atoi(tokens[7].c_str());
	//mapWidth = atoi(tokens[8].c_str());

	//CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
	//tileMap = new CTileMap(pixel, img_path.c_str(), file_path.c_str(), numCol, numRow, numColToRead, numRowToRead, idCell);
	tileMap = new CTileMap();
}

void CWorldMapScene::_ParseSection_TEXTURES(string line)
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

void CWorldMapScene::_ParseSection_SPRITES(string line)
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

void CWorldMapScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CWorldMapScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

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
void CWorldMapScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
		case OBJECT_TYPE_MARIO:
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				return;
			}
			obj = new CMarioWorldMap();
			player = (CMarioWorldMap*)obj;

			DebugOut(L"[INFO] Player object created!\n");
			break;
		case OBJECT_TYPE_CHECKPOINT:
			{
				int left = atoi(tokens[4].c_str());
				int top = atoi(tokens[5].c_str());
				int right = atoi(tokens[6].c_str());
				int bottom = atoi(tokens[7].c_str());

				obj = new CCheckPoint(left, top, right, bottom);
				obj->SetState(CHECKPOINT_STATE_NORMAL);
				DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
			}
			
			break;
		case OBJECT_TYPE_START:
			{
				int left = atoi(tokens[4].c_str());
				int top = atoi(tokens[5].c_str());
				int right = atoi(tokens[6].c_str());
				int bottom = atoi(tokens[7].c_str());

				obj = new CCheckPoint(left, top, right, bottom);
				obj->SetState(CHECKPOINT_STATE_NORMAL);
				obj->SetEnable(false);
				DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
			}
			
			break;
		case OBJECT_TYPE_GRASS:
			obj = new CGrass();
			DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
			break;
		default:
			DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
			return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);

	effect = new CEffect();
	effect->SetPosition(207, 107);
	effect->SetState(0);
	effect->SetAppear(true);
}

void CWorldMapScene::Load()
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
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
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
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"scenes\\textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	CGame::GetInstance()->SetCamPos(0, 0);

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CWorldMapScene::Update(DWORD dt)
{
	coObjects.clear();
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	player->Update(dt, &coObjects);
}

void CWorldMapScene::Render()
{
	tileMap->Render();

	for (int i = 0; i < objects.size(); i++) objects[i]->Render();

	player->Render();

	effect->Render();
}

/*
	Unload current scene
*/
void CWorldMapScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CWorldMapSceneKeyHandler::OnKeyDown(int KeyCode)
{
	CMarioWorldMap* mario = ((CWorldMapScene*)scence)->GetPlayer();

	switch (KeyCode)
	{
	case DIK_S:
		CGame::GetInstance()->SwitchScene(2);
		break;
	case DIK_F1:
		CGame::GetInstance()->SwitchScene(2);
		break;
	case DIK_F2:
		CGame::GetInstance()->SwitchScene(1);
		break;
	}

	if (mario->IsMoving()) return;

	switch (KeyCode)
	{
	case DIK_S:
		CGame::GetInstance()->SwitchScene(2);
		break;
	case DIK_F1:
		CGame::GetInstance()->SwitchScene(2);
		break;
	case DIK_F2:
		CGame::GetInstance()->SwitchScene(1);
		break;
	case DIK_UP:
		if (mario->moveUp)
		{
			mario->SetSpeed(0, -MARIO_VELOCITY);
			mario->SetMoving(true);
		}
		
		break;
	case DIK_DOWN:
		if (mario->moveDown)
		{
			mario->SetSpeed(0, MARIO_VELOCITY);
			mario->SetMoving(true);
		}
		
		break;
	case DIK_LEFT:
		if (mario->moveLeft)
		{
			mario->SetSpeed(-MARIO_VELOCITY, 0);
			mario->SetMoving(true);
		}
		
		break;
	case DIK_RIGHT:
		if (mario->moveRight)
		{
			mario->SetSpeed(MARIO_VELOCITY, 0);
			mario->SetMoving(true);
		}
		
		break;
	}
}

void CWorldMapSceneKeyHandler::OnKeyUp(int KeyCode)
{
	//CMario* mario = ((CWorldMapScene*)scence)->GetPlayer();

	switch (KeyCode)
	{
	case DIK_S:
		break;
	}
}

void CWorldMapSceneKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	//CMario* mario = ((CWorldMapScene*)scence)->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT)) {
		
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		
	}
	/*else
		mario->SetState(MARIO_STATE_IDLE);*/
}