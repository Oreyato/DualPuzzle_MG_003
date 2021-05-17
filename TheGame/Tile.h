#pragma once
#ifndef DEF_TILE
#define DEF_TILE

#include <iostream>
#include "raylib.h"

//class Level;

class Tile
{
public:

	Tile();
	~Tile();

	void TileUpdate(int type);
	void ScreenPosition(int row, int column, int sizeX, int sizeY);
	//void GetScreenInfos(int width, int height);

	//Former Player's classes
	void Inputs();
	void Collision();
	void EffectiveMove();

	int GiveType();
	//void NonOptimisedColl(int typeU, int typeD, int typeL, int typeR);

	void Draw(int frame);
	void BgDraw(int frame);

	void LateDraw(int frame);

protected:
	int m_xPos;
	int m_yPos;
	bool m_once;
	int m_bgX;
	int m_bgY;

	int m_width;
	int m_height;

	int m_screenW;
	int m_screenH;

	int m_tableW;
	int m_tableH;

	int m_type;
	Texture2D m_sprite;
	Texture2D m_spriteBg;

	//Inputs
	int m_up;
	int m_right;

	//Neighbourhood
//	Level* m_level;

	bool m_neighbour;
	int m_typeU;
	int m_typeD;
	int m_typeL;
	int m_typeR;
};

#endif