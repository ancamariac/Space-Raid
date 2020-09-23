#include "raylib.h"
#include <iostream>
using namespace std;

int currentScene = 0;


class Ship {

public:

    float x, y, angle;
    Texture2D redtex, bluetex, greentex, purpletex;

    Ship (){
        x = 0;
        y = 0;
        angle = 0;
        redtex = LoadTexture("assets/redship.png");
        bluetex = LoadTexture("assets/blueship.png");
        greentex = LoadTexture("assets/greenship.png");
        purpletex = LoadTexture("assets/purpleship.png");
    }

    /*void control() {

    }

    void draw() {

    }*/
};


const int screenWidth = 1600;
const int screenHeight = 1000;

class TapToStart {
    public:
        Texture2D logo, background, taptostart;
        float scrollingBack = 0.0f;

        int mouseX = 0, mouseY = 0;
        int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
        bool btnAction = false;         // Button action should be activated
        Vector2 mousePoint = { 0.0f, 0.0f };

        TapToStart () {

            background = LoadTexture("assets/background.png");
            logo = LoadTexture("assets/logov2.png");
            taptostart = LoadTexture("assets/taptostart.png");


        }
        void draw(){

            scrollingBack -= 2.0f;
            if (scrollingBack <= -background.width*2) scrollingBack = 0;

            DrawTextureEx(background, (Vector2){ scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 0 }, 0.0f, 2.0f, WHITE);

            DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2 - 110, WHITE);

            DrawTexture(taptostart, screenWidth/2 - taptostart.width/2, screenHeight/2 - taptostart.height/2 + 330, WHITE);

        }

        void update() {

           if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ) {
                 mouseX = GetMouseX();
                 mouseY = GetMouseY();

                if ( mouseX >= screenWidth/2 - taptostart.width/2 &&
                     mouseX <= screenWidth/2 + taptostart.width/2 &&
                     mouseY >= screenHeight/2 - taptostart.height/2 + 330 &&
                     mouseY <= screenHeight/2 + taptostart.height/2 + 330 ) {

                        currentScene = 1;
                }
           }
        }

};

class Menu {

public:
    Texture2D playgame, options, credits, logo, background;
    float scrollingBack = 0.0f;


    int mouseX = 0, mouseY = 0;

    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;         // Button action should be activated
    Vector2 mousePoint = { 0.0f, 0.0f };

    Vector2 playGamePos;
    Vector2 optionsPos;
    Vector2 creditsPos;

    Menu() {

       logo = LoadTexture("assets/logov2.png");
       credits = LoadTexture("assets/credits.png");
       options = LoadTexture("assets/options.png");
       playgame = LoadTexture("assets/playgame.png");
       background = LoadTexture("assets/background.png");

       playGamePos.x = screenWidth/2 - playgame.width*2;
       playGamePos.y = screenHeight/2 - playgame.height*2 + 250;
       optionsPos.x = screenWidth/2 - options.width*2 - 250;
       optionsPos.y = screenHeight/2 - options.height*2 + 400;
       creditsPos.x = screenWidth/2 - credits.width*2 + 200;
       creditsPos.y = screenHeight/2 - credits.height*2 + 400;

    }

     void draw(){

            scrollingBack -= 2.0f;
            if (scrollingBack <= -background.width*2) scrollingBack = 0;

            DrawTextureEx(background, (Vector2){ scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 0 }, 0.0f, 2.0f, WHITE);

            DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2 - 175, WHITE);

            DrawTextureEx(playgame, playGamePos, 0, 4, WHITE);
            DrawTextureEx(options, optionsPos, 0, 4, WHITE);
            DrawTextureEx(credits, creditsPos, 0, 4, WHITE);

     }

     void update() {


     }
};

class chooseColor {


};
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
    //--------------------------------------------------------------------------------------

    // Main game loop

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
            switch(currentScene) {

                case 0:
                    start.update();
                    break;
                case 1:
                    menu.update();
                    break;
            }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


            ClearBackground(GetColor(0x052c46ff));

            switch(currentScene) {

                case 0:
                    start.draw();
                    break;

                case 1:
                    menu.draw();
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
