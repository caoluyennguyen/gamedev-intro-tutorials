#include "TileMap.h"
#include "Textures.h"
#include "Mario.h"
#include <iostream>
#include <fstream>
#include "Game.h"

using namespace std;

CTileMap::CTileMap(int pixel, LPCWSTR bgImagePath, LPCWSTR filePath, int numCol, int numRow, int numColToRead, int numRowToRead, int idCell)
{
	sprites = CSprites::GetInstance();
	this->pixel = pixel;
	this->bgImagePath = bgImagePath;
	this->filePath = filePath;
	this->numCol = numCol;
	this->numRow = numRow;
	this->numColToRead = numColToRead;
	this->numRowToRead = numRowToRead;
	this->idCell = idCell;

	LoadMap();
}

CTileMap::CTileMap(int textureId, int left, int top, int right, int bottom)
{
	this->textureId = textureId;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

void CTileMap::LoadMap()
{
	// Luu tung tile theo id tu 1, 2, ...
	CTextures* textures = CTextures::GetInstance();
	textures->Add(70, bgImagePath, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texTileMap = textures->Get(70);

	for (int i = 0; i < numRowToRead; i++)
	{
		for (int j = 0; j < numColToRead; j++)
		{
			sprites->Add(idCell, pixel * j, pixel * i, pixel + pixel * j, pixel + pixel * i, texTileMap);
			idCell++;
		}
	}

	ifstream f;
	f.open(filePath);

	// current resource section flag
	int value;
	char str[1024];
	while (f.getline(str, 1024))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		vector<string> tokens = split(line, " ");
		vector<int> lineOfCell;
		DebugOut(L"--> %s\n", ToWSTR(line).c_str());

		for (int i = 0; i < tokens.size(); i++)	// why i+=2 ?  sprite_id | frame_time  
		{
			if (atoi(tokens[i].c_str())) lineOfCell.push_back(atoi(tokens[i].c_str()));
		}
		cellId.push_back(lineOfCell);
	}

	f.close();
}

void CTileMap::Render()
{
	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(textureId);

	float l, t, r, b;

	CGame::GetInstance()->Draw(0, 0, bbox, this->left, this->top, this->right, this->bottom);
}

void CTileMap::Render(int x)
{
	int start, finish;
	/*if (Simon::GetInstance()->IsFightingBoss()) {
		start = 23;
		finish = 48;
	}
	else {
		start = x / pixel - 12;
		finish = start + 29;
	}*/

	// fix start and finish
	start = x / pixel;
	finish = start + 20;

	if (start < 0)
	{
		start = 0;
	}
	if (finish > numCol)
	{
		finish = numCol;
	}
	for (int i = 0; i < numRow; i++)
	{
		for (int j = start; j < finish; j++)
		{
			sprites->Get(cellId[i][j])->Draw(j * pixel, i * pixel);
		}
	}
}