#include "ChooseColor.h"
#include "Constants.h"
#include "Helpers.h"
#include "raylib.h"
#include "Scenes.h"

ChooseColor::ChooseColor () {

    backButton = LoadTexture("assets/back.png");
    backPos.x = screenWidth/2 - backButton.width - 600;
    backPos.y = screenHeight/2 - backButton.height - 350;

    nextButton = LoadTexture("assets/next.png");
    nextPos.x = screenWidth/2 + nextButton.width + 250;
    nextPos.y = screenHeight/2 - nextButton.height - 350;

    blueShipButton.configure(300,500,1);
    redShipButton.configure(550,500,2);
    greenShipButton.configure(800,500,3);
    purpleShipButton.configure(1050,500,4);
}

void ChooseColor::draw () {

    blueShipButton.draw();
    redShipButton.draw();
    greenShipButton.draw();
    purpleShipButton.draw();

    if ( isNextButtonActive () )
        DrawTextureEx(nextButton, nextPos, 0, 2, WHITE ); // transparency off
    else
        DrawTextureEx(nextButton, nextPos, 0, 2, (Color){ 255, 255, 255, 127 } ); // transparency on

    DrawTextureEx(backButton, backPos, 0, 2, WHITE);
}

void ChooseColor::update() {

    blueShipButton.update();
    redShipButton.update();
    greenShipButton.update();
    purpleShipButton.update();

    if ( IsRecClicked ( MOUSE_LEFT_BUTTON, backPos.x, backPos.y, backButton.width * 2, backButton.height * 2) ) {

        currentScene = Scenes::MainMenu;
    }

}

bool ChooseColor::isNextButtonActive () {
    int sum =   blueShipButton.isActive()
    +           redShipButton.isActive()
    +           greenShipButton.isActive()
    +           purpleShipButton.isActive();

    return sum >= 2;
}
