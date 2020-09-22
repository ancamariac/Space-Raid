#include "raylib.h"
#include <iostream>
using namespace std;
#define NUM_FRAMES  3       // Number of frames (rectangles) for the button sprite texture

/*class Ship {
private:
protected:
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

    void control() {

    }

    void draw() {

    }
};
*/

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
           mouseX = GetMouseX();
           mouseY = GetMouseY();
           if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ) {
                 mouseX = GetMouseX();
                 mouseY = GetMouseY();

                if ( mouseX >= screenWidth/2 - taptostart.width/2 && mouseX <= screenWidth/2 + taptostart.width/2 &&
                    mouseY >= screenHeight/2 - taptostart.height/2 + 330 && mouseY <= screenHeight/2 + taptostart.height/2 + 330 ) {

                        cout<<"merge";
                }
           }
        }

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
    //--------------------------------------------------------------------------------------

    // Main game loop

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
            start.update();

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


            ClearBackground(GetColor(0x052c46ff));

            start.draw();




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
