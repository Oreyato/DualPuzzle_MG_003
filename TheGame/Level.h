#pragma once

#ifndef DEF_LEVEL
#define DEF_LEVEL

#include "Tile.h"

class Level
{
public:
	Level();
	~Level();

	void CreateLevel(int currentLevel);

	int GetType(int searchingFor);

	void Update(int frame);
	
private:
	//Not used right now =================================

	int m_row;
	int m_column;
	
	//int m_table; //pointers issue, I guess
	//====================================================
	
	Tile tile[128];
};

#endif
