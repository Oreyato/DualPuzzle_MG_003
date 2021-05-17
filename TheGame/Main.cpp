#include <math.h> 
#include <stdio.h>  
#include <vector>

#include "Level.h"

using namespace std;

#pragma region Initialization
//Initialization -----------------------------------------------------------------------
///Headers
Tile tile;
Level level;
/*
PlayerA playerA;
PlayerB playerB;
*/

///Functions
void Start();
void Update();
void Draw();

///Type and Structures Definition
typedef enum GameScreen { LOGO = 0, TITLE, LEVEL_1, REFRESH, ENDING} GameScreen;
GameScreen currentScreen = LOGO;
int framesCounter = 0;
int refresh = 0;

///Screen
const int scaling = 2;

const int screenWidth = 256*scaling;
const int screenHeight = 256*scaling;

//======================================================================
//TEMP 
//======================================================================

float timer = 0;
int frame = 0;

//======================================================================
//======================================================================

///Cells
const int cellWidth = 16*scaling;
const int cellHeight = 16*scaling;

///Grid
const int gridWidth = screenWidth / cellWidth;
const int gridHeight = screenHeight / cellHeight;

///Levels
int currentLevel = 0;

///Textures
Texture2D t_start;

Texture2D t_PlayerA;
Texture2D t_PlayerB;

Texture2D t_EndA;
Texture2D t_EndB;

Texture2D t_Bg;

Texture2D t_Out;
Texture2D t_Obst;
//--------------------------------------------------------------------------------------
#pragma endregion

int main(int argc, char* argv[])
{
    #pragma region Init
    //Initialization -----------------------------------------------------------------------
    ///Window
    InitWindow(screenWidth, screenHeight, "PuzzleGame");
    SetTargetFPS(60);

    //tile.GetScreenInfos(screenWidth, screenHeight);

    //--------------------------------------------------------------------------------------
    #pragma endregion

    Start();

    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    CloseWindow();

    return 0;
}

void Start()
{
    //LoadTextures
    t_start = LoadTexture("../resources/Textures/DualPuzzleStarting.png");

    t_PlayerA = LoadTexture("../resources/Textures/t_PlayerA.png");
    t_PlayerB = LoadTexture("../resources/Textures/t_PlayerB.png");
    t_EndA = LoadTexture("../resources/Textures/t_EndA.png");
    t_EndB = LoadTexture("../resources/Textures/t_EndB.png");
    t_Bg = LoadTexture("../resources/Textures/t_Bg.png");
    t_Out = LoadTexture("../resources/Textures/t_Out.png");
    t_Obst = LoadTexture("../resources/Textures/t_Obstacle.png");

    /*TO ERASE
    playerA.GetTexture(t_PlayerA);
    playerB.GetTexture(t_PlayerB);
    
    tile.GetTexture(t_Obst);
    */
}

void Update() 
{
    timer += GetFrameTime();

    if (timer >= 0.2f)
    {
        timer = 0.0f;
        frame += 1;
    }

    frame = frame % 3;

    switch (currentScreen) {
        case LOGO:
        {
            framesCounter++;    // Count frames

            // Wait for 5 seconds (300 frames) before jumping to LEVEL_1 screen
            if (framesCounter > 300)
            {
                currentScreen = LEVEL_1;
                currentLevel = 1;
                framesCounter = 0;
            }
        } break;
        case TITLE:
        {
            // Press enter to change to LEVEL_1 screen
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = LEVEL_1;
                currentLevel = 1;
            }
        } break;
        //===============================================================================================================================================================
        //======================================================================LEVELS===================================================================================
        case LEVEL_1:
        {
            //Create Level once
            if (currentLevel == 1) {
                level.CreateLevel(currentLevel);

                currentLevel = 0;
            }

            /*
            // Press enter to change to ENDING screen
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = ENDING;
            }
            */
        } break;

        //===============================================================================================================================================================
        //===============================================================================================================================================================
        case REFRESH:
        {
            // When the player collides with the red tiles
            framesCounter++;

            if (framesCounter > 3) 
            {
                refresh++;
                framesCounter = 0;
            }

            if (refresh >= 4)
            {
                refresh = 0;
                currentScreen = LEVEL_1; // ======================UNFINISHED=============================
            }
        } break;

        case ENDING:
        {
            // Press enter to return to TITLE screen
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = TITLE;
            }
        } break;
        default: break;
    }
}

void Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (currentScreen)
    {
        case LOGO:
        {
            DrawTexture(t_start, 0, 0, WHITE);

            if (frame == 0) {
                DrawText("LOADING.", 5, screenHeight - 20, 20, BLACK);
            }
            else if (frame == 1) {
                DrawText("LOADING..", 5, screenHeight - 20, 20, BLACK);
            }
            else
            {
                DrawText("LOADING...", 5, screenHeight - 20, 20, BLACK);
            }

        } break;
        case TITLE:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
            DrawText("DUAL PUZZLE", 20, 20, 40, LIGHTGRAY);
            DrawText("PRESS ENTER to play FIRST LEVEL", 120, 220, 20, GRAY);

        } break;

        //LEVELS=======================================================================================

        case LEVEL_1:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
            DrawText("LEVEL 1", 20, 20, 40, LIGHTGRAY);

            /*
            for (int i = 0; i < 126; i++)
            {
                tile[i].Draw(frame);
            }

            */

            level.Update(frame);

        } break;

        //=============================================================================================

        case REFRESH:
        {
            //"Death" feedback
            if (refresh % 2 == 0) 
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, RED);
            }
            else
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, LIGHTGRAY);
            }
            //DrawText(TextFormat("%i", refresh), 20, 20, 50, GREEN);

        } break;
        case ENDING:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

        } break;
        default: break;
    }

    EndDrawing();
}



