#pragma once
#include "Cell.h"

#define GRID_SECTION_SETTINGS	1
#define GRID_SECTION_OBJECTS	2
#define MAX_GRID_LINE 1024

class CGrid
{
	int numRow, numCol;
	int cellWidth;
	Cell** cells;
	//vector<vector<LPCELL>> cells;
	vector<LPGAMEOBJECT>* listObject;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_OBJECTS(string line);
public:
	CGrid(LPCWSTR filePath, vector<LPGAMEOBJECT>* listObject);
	void GetListObject(vector<LPGAMEOBJECT>* listObject, int camX, int camY);
	void Load(LPCWSTR filePath, vector<LPGAMEOBJECT>* listObject);
	void Unload();
};

