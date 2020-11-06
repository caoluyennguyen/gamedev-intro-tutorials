//#pragma once
//#include <d3dx9.h>
//#include <algorithm>
//
//class CTileMap
//{
//public:
//	CTileMap();
//	void Render();;
//};

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "Utils.h"
#include "Sprites.h"

class CTileMap
{
	CTileMap* _instance;

	int pixel = 32;
	int idCell;
	int x = 0;				// toa do x cua sprite dau tien tren cung
	int y = 0;				// toa do y cua sprite dau tien tren cung

	int numCol = 48;		// so cot can de ve
	int numColToRead = 17;		// so cot can de ve
	//int numCol = 16;		// so cot can de ve
	int numRow = 10;		// so hang can de ve
	int numRowToRead = 4;		// so hang can de ve
	//int numRow = 12;		// so hang can de ve

	int mapWidth;			// chieu rong cua map
	int mapHeight;			// chieu cao cua map

	int cellWidth = 32;		// chieu rong cua mot o
	int cellHeight = 32;	// chieu cao cua mot o

	vector<vector<int>> cellId;

	CSprites* sprites;
	LPCWSTR filePath;
	LPCWSTR bgImagePath;
public:
	CTileMap() {};
	CTileMap(int pixel, LPCWSTR bgImagePath, LPCWSTR filePath, int numCol, int numRow, int numColToRead, int numRowToRead, int idCell);
	void LoadMap();
	void Render();
	void Render(int x);
	void UnLoad() { sprites->Clear(); };

	CTileMap* GetInstance();
};

