#include "Level.h"
#include <iostream>

using namespace std;

Level::Level()
{
	m_row = 0;
	m_column = 0;

	//m_table[0][0];
}

Level::~Level()
{
}

void Level::CreateLevel(int currentLevel)
{
	switch (currentLevel)
	{
	case 1:
	{
		//Create Table, based on level size (documents)
		m_row = 14;
		m_column = 9;

		//int m_table[m_sizeX][m_sizeY];

		int const tempRow = 14;
		int const tempColumn = 9;

		int m_table[tempRow][tempColumn];

		//============================================ Fill table with documents infos ============================================
		///Key: 1-PlayerA, 2-PlayerB, 3-EndA, 4-EndB, 8-Obstacle, 9-Borders and 0-Background
		///Filling with 0
		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_column; j++)
			{
				m_table[i][j] = 0;
			}
		}

		///Fill borders with 9 
		for (int i = 0; i < m_row; i++) //Top&Bottom
		{
			m_table[i][0] = 9;
			m_table[i][m_column - 1] = 9;
		}
		for (int j = 0; j < m_column; j++) //Right&Left
		{
			m_table[0][j] = 9;
			m_table[m_row - 1][j] = 9;
		}
		 
		#pragma region Adding coordinates by hand
		///AI Improvement here?
		///PlayerA & PlayerB pos
		m_table[1][2] = 1;
		m_table[10][1] = 2;

		///EndA & EndB pos
		m_table[6][7] = 3;
		m_table[8][4] = 4;

		///Obstacles pos
		for (int i = 1; i <= 4; i++)
		{
			m_table[i][1] = 8;
		}
		for (int i = 9; i <= 12; i++)
		{
			m_table[i][4] = 8;
		}
		m_table[9][1] = 8;
		m_table[4][2] = 8;
		m_table[4][3] = 8;
		m_table[5][4] = 8;
		m_table[5][5] = 8;
		m_table[1][5] = 8;
		m_table[2][5] = 8;
		#pragma endregion

		//===========================================================================================================================

		//============================================== Putting infos in Tile instance =============================================
		//Add number to create new instances
		int currentInstance = 0;

		//Sending Infos to Tiles
		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_column; j++)
			{
				tile[currentInstance].TileUpdate(m_table[i][j]);
				tile[currentInstance].ScreenPosition(i, j, m_row, m_column);

				currentInstance++;
			}
		}

		//Testing (reading each line as if it was top to bottom on the document)
		cout << "Level " << currentLevel << " structure:" << endl;

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_column; j++)
			{
				cout << m_table[i][j];
			}
			cout << endl;
		}

		//=============================================================================================================================


	}break;
	case 2:
	{

	}break;
	case 3:
	{

	}break;
	default:
		break;
	}
}

int Level::GetType(int searchingFor)
{
	int type = 0;
	//type = tile[searchingFor].GiveType();
	return type;
}

void Level::Update(int frame)
{
	// =====================================================Not exactly what I wanted=======================================================
	/*
	//int i = m_column because the first line is made of 9 =====actually the column here, changing this would be great
	//126 - m_row because the last line is made of 9 =================================================================
	//little optimisation for something that is not optimised at all
	for (int i = m_column; i < 126 - m_column; i++)
	{
		//tile[i].NonOptimisedColl(tile[i - 1].GiveType(), tile[i - m_column].GiveType(), tile[i - m_column].GiveType(), tile[i + 1].GiveType());
		tile[i].EffectiveMove();
	}
	*/
	// =====================================================================================================================================

	for (int i = 0; i < 126; i++)
	{
		tile[i].EffectiveMove();
		tile[i].Draw(frame);
	}

	for (int i = 0; i < 126; i++)
	{
		tile[i].LateDraw(frame);
	}
}
