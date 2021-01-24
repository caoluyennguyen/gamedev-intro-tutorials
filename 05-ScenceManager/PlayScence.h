#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "TileMap.h"
#include "FireBall.h"
#include "Grid.h"
#include "CamCheck.h"

class CPlayScene: public CScene
{
protected: 
	CMario *player;					// A play scene has to have player, right? 
	CTileMap* tileMap;
	CGrid* grid;
	CCamCheck* camCheck;

	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> objects;

	float minX, maxX, minY, maxY;

	void _ParseSection_TILEMAP(string line);
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_GRID(string line);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario * GetPlayer() { return player; } 

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

