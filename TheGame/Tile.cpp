#include "Tile.h"
//#include "Level.h"

using namespace std;

Tile::Tile()
{
    m_xPos = 0;
    m_yPos = 0;
    m_once = true;
    m_bgX = 0;
    m_bgY = 0;

    m_width = 0;
    m_height = 0;

    m_screenH = 512;
    m_screenW = 512;

    m_tableW = 0;
    m_tableH = 0;

    m_type = 0;

    m_up = 0;
    m_right = 0;

    m_neighbour = false;

    m_typeU = 0;
    m_typeD = 0;
    m_typeL = 0;
    m_typeR = 0;

}

Tile::~Tile() //Destructor, needed for "LEGACY"
{
}

void Tile::TileUpdate(int type)
{
    m_type = type;

    //A lot of LOAD, not optimised, I should have created them in the Start function (Main.cpp) ==================== working on it ================================
    switch (type)
    {
    case 1:
    {
        m_sprite = LoadTexture("../resources/Textures/t_PlayerA.png");
    }break;
    case 2:
    {
        m_sprite = LoadTexture("../resources/Textures/t_PlayerB.png");
    }break;
    case 3:
    {
        m_sprite = LoadTexture("../resources/Textures/t_EndA.png");
    }break;
    case 4:
    {
        m_sprite = LoadTexture("../resources/Textures/t_EndB.png");
    }break;
    case 8:
    {
        m_sprite = LoadTexture("../resources/Textures/t_Obstacle.png");
    }break;
    case 9:
    {
        m_sprite = LoadTexture("../resources/Textures/t_Out.png");
    }break;
    case 0:
    {
        m_sprite = LoadTexture("../resources/Textures/t_Bg.png");
    }break;

    default:
    {
        cout << "ERROR: Tile.cpp, texture load" << endl;
    }
    break;
    }

    m_width = m_sprite.width;
    m_height = m_sprite.height;
}

void Tile::ScreenPosition(int row, int column, int sizeX, int sizeY)
{
    
    //Debug
    cout << m_xPos << " -> ";
    m_xPos++;
    cout << m_xPos << endl;

    //ISSUE THERE ===============================================================================================
    //m_screenW got an error, incredibly high number for some reason
    cout << "m_screenW: " << m_screenW << endl;

    //Number of possible boxes
    int possibleWidth = 0;
    possibleWidth = m_screenW / (m_width/3);
    int possibleHeight = 0;
    possibleHeight = m_screenH / m_height;

    cout << "m_screenW: " << m_screenW << endl;

    //Centering the Level
    int minX = (possibleWidth - sizeX) / 2;
    int minY = (possibleHeight - sizeY) / 2;

    //Converting into new position
    m_xPos = (minX + row) * (m_width/3);
    m_yPos = (minY + column) * m_height;
    
    //============================================================================================================

}

void Tile::Inputs()
{
    if (IsKeyPressed(KEY_UP) && m_typeU != 8)
    {
        m_up = -1;
    }
    else if (IsKeyPressed(KEY_DOWN) && m_typeD != 8)
    {
        m_up = 1;
    }
    else if (IsKeyPressed(KEY_RIGHT) && m_typeR != 8)
    {
        m_right = 1;
    }
    else if (IsKeyPressed(KEY_LEFT) && m_typeL != 8)
    {
        m_right = -1;
    }
    else
    {
        m_up = 0;
        m_right = 0;
    }
}

void Tile::Collision()
{
    //m_level.GetType(16);

    m_neighbour = true;
}

void Tile::EffectiveMove()
{
    if (m_type == 1 || m_type == 2)
    {
        Collision();

        if (m_neighbour) {
            Inputs();

            m_yPos += 16 * m_up;
            m_xPos += 16 * m_right;
        }
    }
}

int Tile::GiveType()
{
    return m_type;
}

/* 
// ====================================== Only working for the first movement ==================================================

void Tile::NonOptimisedColl(int typeU, int typeD, int typeL, int typeR)
{
    m_typeU = typeU;
    m_typeD = typeD;
    m_typeL = typeL;
    m_typeR = typeR;
}
// =============================================================================================================================
*/

void Tile::Draw(int frame)
{
    //Cutting the frame at the right place (one third, only three frames) to create an animation

    float oneThird = m_sprite.width / 3;

    //cout << m_xPos << endl;

    DrawTextureRec(
        m_sprite, //The sprite we want
        Rectangle{ oneThird * frame, 0, oneThird, oneThird }, //Cutting what we don't want
        Vector2{ (float)m_xPos, (float)m_yPos }, //Position in the game
        WHITE);

    if (m_type == 1 || m_type == 2) {
        if (m_once) {
            m_bgX = m_xPos;
            m_bgY = m_yPos;

	        m_spriteBg = LoadTexture("../resources/Textures/t_Bg.png");

            m_once = false;
        }
        BgDraw(frame);
    }
}

void Tile::BgDraw(int frame)
{
    //Cutting the frame at the right place (one third, only three frames) to create an animation

    float oneThird = m_sprite.width / 3;

    //cout << m_xPos << endl;

    DrawTextureRec(
        m_spriteBg, //The sprite we want
        Rectangle{ oneThird * frame, 0, oneThird, oneThird }, //Cutting what we don't want
        Vector2{ (float)m_bgX, (float)m_bgY }, //Position in the game
        WHITE);
}

void Tile::LateDraw(int frame)
{
    if (m_type == 1 || m_type == 2) {
        //Cutting the frame at the right place (one third, only three frames) to create an animation

        float oneThird = m_sprite.width / 3;

        //cout << m_xPos << endl;

        DrawTextureRec(
            m_sprite, //The sprite we want
            Rectangle{ oneThird * frame, 0, oneThird, oneThird }, //Cutting what we don't want
            Vector2{ (float)m_xPos, (float)m_yPos }, //Position in the game
            WHITE);
    }
}
