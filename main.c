#include "raylib.h"
#include <iostream>
using namespace std;

enum class Scenes {
TapToStart,
MainMenu,
ChooseColors
};

Scenes currentScene = Scenes::TapToStart;

/* Check if a rectangle on-screen is clicked */
bool IsRecClicked ( int button, int x, int y, int w, int h ) {
    if ( IsMouseButtonPressed(button) ) {
        Vector2 mousePos = GetMousePosition();


        if ( mousePos.x >= x && mousePos.x <= x+w
            && mousePos.y >= y && mousePos.y <= y+h )
            return true;
    }

    return false;
}

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
        Texture2D logo, taptostart;

        int mouseX = 0, mouseY = 0;
        int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
        bool btnAction = false;         // Button action should be activated
        Vector2 mousePoint = { 0.0f, 0.0f };

        TapToStart () {
            logo = LoadTexture("assets/logov2.png");
            taptostart = LoadTexture("assets/taptostart.png");


        }
        void draw(){

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

                        currentScene = Scenes::MainMenu;
                }
           }
        }

};

class Menu {

public:
    Texture2D playgame, options, credits, logo;


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

       playGamePos.x = screenWidth/2 - playgame.width*2;
       playGamePos.y = screenHeight/2 - playgame.height*2 + 250;
       optionsPos.x = screenWidth/2 - options.width*2 - 250;
       optionsPos.y = screenHeight/2 - options.height*2 + 400;
       creditsPos.x = screenWidth/2 - credits.width*2 + 200;
       creditsPos.y = screenHeight/2 - credits.height*2 + 400;

    }

     void draw(){

            DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2 - 175, WHITE);

            DrawTextureEx(playgame, playGamePos, 0, 4, WHITE);
            DrawTextureEx(options, optionsPos, 0, 4, WHITE);
            DrawTextureEx(credits, creditsPos, 0, 4, WHITE);

     }

     void update() {
        if ( IsRecClicked( MOUSE_LEFT_BUTTON, playGamePos.x, playGamePos.y, playgame.width*4, playgame.height*4 ) ) {
            currentScene = Scenes::ChooseColors;
        }
     }
};

class ChooseColorButton {
private:
    void setNumber( int n ){
        switch ( n ) {
            case 1:
                pTex = LoadTexture("assets/1p.png");
                shipTex = LoadTexture("assets/blueship.png");
                break;
            case 2:
                pTex = LoadTexture("assets/2p.png");
                shipTex = LoadTexture("assets/redship.png");
                break;
            case 3 :
                pTex = LoadTexture("assets/3p.png");
                shipTex = LoadTexture("assets/greenship.png");
                break;
            case 4:
                pTex = LoadTexture("assets/4p.png");
                shipTex = LoadTexture("assets/purpleship.png");
                break;
        }

        shipPos.x = x+width-shipTex.width*4-10;
        shipPos.y = y+10;
    }

    void setPosition( int _x , int _y ){
        x = _x;
        y = _y;
    }

    bool active = false;

public:
    int x = 0, y = 0;
    const int width = 200;
    const int height = 100;

    Texture2D pTex;
    Texture2D shipTex;

    Vector2 shipPos;
    Vector2 pPos;

    void configure( int _x, int _y, int color ) {
        setPosition(_x,_y);
        setNumber(color);
    }

    void draw() {

        if ( active ){
            // Draw rectangle + white border
            DrawRectangle(x, y, width, height, ORANGE);
            DrawRectangleLines(x+2, y+2, width-4, height-4, WHITE);

            // Draw p and ship
            DrawTextureEx(shipTex, shipPos, 0, 4, WHITE);
            DrawTexture(pTex, x+10, y+10, WHITE);
        } else {
            // Draw rectangle + white border
            DrawRectangle(x, y, width, height, GRAY);
            DrawRectangleLines(x+2, y+2, width-4, height-4, WHITE);
        }


    }

    void update() {
        if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ){
            Vector2 mousePos = GetMousePosition();

            if ( mousePos.x >= x && mousePos.x <= x + width &&
                 mousePos.y >= y && mousePos.y <= y + height
                )
            active = !active;
        }
    }

    bool getActive() {
        return active;
    }
};

class ChooseColor {
public:

    ChooseColorButton blueShipButton, redShipButton, greenShipButton, purpleShipButton;

    ChooseColor () {
        blueShipButton.configure(300,500,1);
        redShipButton.configure(550,500,2);
        greenShipButton.configure(800,500,3);
        purpleShipButton.configure(1050,500,4);
    }

    void draw () {
        blueShipButton.draw();
        redShipButton.draw();
        greenShipButton.draw();
        purpleShipButton.draw();
    }

    void update() {
        blueShipButton.update();
        redShipButton.update();
        greenShipButton.update();
        purpleShipButton.update();
    }


};

class BackgroundRenderer {
public:
    Texture2D background;
    float scrollingBack = 0.0f;
    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;         // Button action should be activated
    Vector2 mousePoint = { 0.0f, 0.0f };

    BackgroundRenderer () {
        background = LoadTexture("assets/background.png");
    }

    void draw(){

        scrollingBack -= 2.0f;
        if (scrollingBack <= -background.width*2) scrollingBack = 0;

        DrawTextureEx(background, (Vector2){ scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
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
    Menu menu;
    ChooseColor colors;
    BackgroundRenderer bkgr;
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
                case Scenes::ChooseColors:
                    colors.update();
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

                case Scenes::ChooseColors:
                    colors.draw();
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
