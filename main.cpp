#include "raylib.h"
#include <iostream>
using namespace std;

#include "Scene.h"

class Ship : public Drawable, public Updateable {
private:
    float x, y;
    float angle;
public:
    Ship() {
        x = 0;
        y = 0;
    }
    void update();
    //void draw();
    void draw();
};

#define SHIP_SPEED 10

void Ship::update(){
    if ( IsKeyDown(KEY_W) ){
        y-= SHIP_SPEED;
    }
    if ( IsKeyDown(KEY_S) ){
        y+= SHIP_SPEED;
    }
    if ( IsKeyDown(KEY_A) ){
        x-= SHIP_SPEED;
    }
    if ( IsKeyDown(KEY_D) ){
        x+= SHIP_SPEED;
    }
}

void Ship::draw() {
    DrawRectangle(x,y,100,100,YELLOW);
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Space Raid");

    /* InitAudioDevice();      // Initialize audio device */

    Texture2D background = LoadTexture("assets/background.png");

    Texture2D logo = LoadTexture("assets/logov2.png");

    //Texture2D tap_to_start = LoadTexture("assets/taptostart.png");

    /* Sound fxButton = LoadSound("resources/buttonfx.wav");   // Load button sound */

    float scrollingBack = 0.0f;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    Scene * currentScene;


    Ship * myship = new Ship();
    Scene * playScene = new Scene();
    currentScene = playScene;
    playScene->addDrawable(myship);
    playScene->addUpdateable(myship);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        scrollingBack -= 2.0f;

        if (scrollingBack <= -background.width*2) scrollingBack = 0;


        currentScene->update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));



            // Draw background image twice
            // NOTE: Texture is scaled twice its size
            DrawTextureEx(background, (Vector2){ scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 0 }, 0.0f, 2.0f, WHITE);

            // Draw logo image
            DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2 - 110, WHITE);



            currentScene->draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);  // Unload background texture
    UnloadTexture(background);  // Unload logo texture
    /* UnloadSound(fxButton);      // Unload button sound */

    delete playScene;
    delete myship;

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
