#include "raylib.h"
#include <iostream>
#include "Helpers.h"
#include "ChooseColor.h"
#include "Scenes.h"
#include "Constants.h"
#include "BackgroundRenderer.h"
#include "TapToStart.h"
#include "Menu.h"
#include "GameScene.h"
#include "Ship.h"

using namespace std;

GameScene * gameSceneReference = 0;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "Space Raid");

    /* InitAudioDevice();      // Initialize audio device */

    /* Sound fxButton = LoadSound("resources/buttonfx.wav");   // Load button sound */

    SetTargetFPS(60);

    TapToStart start;
    Menu menu;
    ChooseColor colors;
    BackgroundRenderer bkgr;
    GameScene gameScene;
    gameSceneReference = &gameScene;
    //--------------------------------------------------------------------------------------

    // Main game loop

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
            switch(currentScene) {

                case Scenes::TapToStart:
                    start.update();
                    break;
                case Scenes::MainMenu:
                    menu.update();
                    break;
                case Scenes::ChooseColor:
                    colors.update();
                    break;
                case Scenes::GameScene:
                    gameScene.update();
                    break;
            }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


            ClearBackground(GetColor(0x052c46ff));

            bkgr.draw();

            switch(currentScene) {

                case Scenes::TapToStart:
                    start.draw();
                    break;

                case Scenes::MainMenu:
                    menu.draw();
                    break;

                case Scenes::ChooseColor:
                    colors.draw();
                    break;
                case Scenes::GameScene:
                    gameScene.draw();
                    break;

            }


        EndDrawing();

        //----------------------------------------------------------------------------------
    }


    // De-Initialization
    //--------------------------------------------------------------------------------------
    /*UnloadTexture(background);  // Unload background texture
    UnloadTexture(logo);  // Unload logo texture

    /* UnloadSound(fxButton);      // Unload button sound */

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
