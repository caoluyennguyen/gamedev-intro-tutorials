#include "Grid.h"
#include "Utils.h"
#include "Game.h"
#include <iostream>
#include <fstream>

CGrid::CGrid(LPCWSTR filePath, vector<LPGAMEOBJECT>* listObject)
{
	this->listObject = listObject;
	DebugOut(L"[INFO] Start loading grid resources from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	// current resource section flag
	int section;

	char str[MAX_GRID_LINE];
	while (f.getline(str, MAX_GRID_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") {
			section = GRID_SECTION_SETTINGS; continue;
		}
		if (line == "[OBJECTS]") {
			section = GRID_SECTION_OBJECTS; continue;
		}
		//
		// data section
		//
		switch (section)
		{
		case GRID_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GRID_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene resources %s\n", filePath);
}

void CGrid::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	cellWidth = atoi(tokens[0].c_str());
	numCol = atoi(tokens[1].c_str());
	numRow = atoi(tokens[2].c_str());

	cells = new LPCELL[numRow];
	for (int i = 0; i < numRow; i++)
	{
		cells[i] = new Cell[numCol];
	}
}

void CGrid::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	if (tokens.size() < 1) return; // skip invalid lines

	int cellX = atoi(tokens[0].c_str());
	int cellY = atoi(tokens[1].c_str());
	int objectId;

	for (int i = 2; i < tokens.size(); i++)
	{
		objectId = atoi(tokens[i].c_str());
		cells[cellX][cellY].Add(listObject->at(objectId), objectId);
	}
}

void CGrid::Load(LPCWSTR filePath, vector<LPGAMEOBJECT>* listObject)
{
	this->listObject = listObject;
	DebugOut(L"[INFO] Start loading grid resources from : %s \n", filePath);

	ifstream f;
	f.open(filePath);

	// current resource section flag
	int section;

	char str[MAX_GRID_LINE];
	while (f.getline(str, MAX_GRID_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") {
			section = GRID_SECTION_SETTINGS; continue;
		}
		if (line == "[OBJECTS]") {
			section = GRID_SECTION_OBJECTS; continue;
		}
		//
		// data section
		//
		switch (section)
		{
		case GRID_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GRID_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene resources %s\n", filePath);
}

void CGrid::GetListObject(vector<LPGAMEOBJECT>* listObject, int camX, int camY)
{
	listObject->clear();

	int left, top, right, bottom;
	int i, j, k;
	left = camX / cellWidth;
	top = camY / cellWidth;
	/*right = (int)(camX + 320) / cellWidth
		+ ((int)(camX + 320) % cellWidth ? 1 : 0);
	bottom = (int)(camY + 240) / cellWidth
		+ ((int)(camY + 240) % cellWidth ? 1 : 0);*/
	right = left + 1;
	bottom = top + 1;

	LPGAMEOBJECT obj;

	if (right < 0 || left > numCol || bottom < 0 && top > numRow)
	{
		return;
	}

	if (right > numCol)
	{
		right = numCol;
	}
	if (bottom > numRow)
	{
		bottom = numRow;
	}
	if (left < 0)
	{
		left = 0;
	}
	if (top > 0)
	{
		top = 0;
	}

	LPCELL cell;
	for (i = left; i < right; i++)
	{
		for (j = top; j < bottom; j++)
		{
			cell = &cells[i][j];
			if (cell)
			{
				if (cells[i][j].GetListObjects().size() != 0)
				{
					for (k = 0; k < cells[i][j].GetListObjects().size(); k++)
					{
						obj = cells[i][j].GetListObjects().at(k);
						if (obj->enable == false) continue;
							listObject->push_back(obj);
						/*if (obj->enable == false) continue;
						if (CheckObjectId(listObject, obj)) {
							listObject->push_back(obj);
						}*/
					}
				}
			}

		}
	}
}

void CGrid::Unload()
{
	if (cells)
	{
		for (int i = 0; i < numCol; i++)
		{
			for (int j = 0; j < numRow; j++)
			{
				cells[i][j].Unload();
			}
		}
		delete cells;
		cells = NULL;
	}
}

bool CGrid::CheckObjectId(vector<LPGAMEOBJECT>* listObjects, LPGAMEOBJECT obj)
{
	for (int i = 0; i < listObjects->size(); i++)
	{
		if (listObjects->at(i) == obj) {
			return false;
		}
	}
	return true;
}