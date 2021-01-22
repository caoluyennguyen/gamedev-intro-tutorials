#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "Utils.h"
#include "Sprites.h"

#define NUM_OF_COL 15

class CTileMap
{
	//CTileMap* _instance;

	int pixel;
	int idCell;
	int x;				// toa do x cua sprite dau tien tren cung
	int y;				// toa do y cua sprite dau tien tren cung

	int numCol;				// so cot can de ve
	int numColToRead;		// so cot can de ve

	int numRow;				// so hang can de ve
	int numRowToRead;		// so hang can de ve

	int mapWidth;			// chieu rong cua map
	int mapHeight;			// chieu cao cua map

	int cellWidth;			// chieu rong cua mot o
	int cellHeight;			// chieu cao cua mot o

	int left, top, right, bottom;

	vector<vector<int>> cellId;

	CSprites* sprites;
	LPCWSTR filePath;
	LPCWSTR bgImagePath;
	int textureId;
public:
	CTileMap() {};
	CTileMap(int textureId, int left, int top, int right, int bottom);
	CTileMap(int pixel, LPCWSTR bgImagePath, LPCWSTR filePath, int numCol, int numRow, int numColToRead, int numRowToRead, int idCell);
	void LoadMap();
	void Render();
	void Render(int x);
	void UnLoad() { sprites->Clear(); };

	//CTileMap* GetInstance();
};

