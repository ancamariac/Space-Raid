#include "ChooseColor.h"
#include "Constants.h"
#include "Helpers.h"
#include "raylib.h"
#include "Scenes.h"

bool playingShips[4];
int shipsNumber = 0;

#include <iostream>
using namespace std;

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
    if ( IsRecClicked ( MOUSE_LEFT_BUTTON, nextPos.x, nextPos.y, nextButton.width * 2, nextButton.height * 2) ) {
        if ( isNextButtonActive() ){

            // Memorize what ships are playing
            playingShips[0] = blueShipButton.isActive();
            playingShips[1] = redShipButton.isActive();
            playingShips[2] = greenShipButton.isActive();
            playingShips[3] = purpleShipButton.isActive();

            // Memorize the number of playing ships
            shipsNumber = calculatePlayingShipsSum();

            // Switch to gameScene and call the setup routine
            currentScene = Scenes::GameScene;
            gameSceneReference->setupScene();
        }
    }

}

bool ChooseColor::isNextButtonActive () {
    return calculatePlayingShipsSum() >= 2;
}

int ChooseColor::calculatePlayingShipsSum()
{
    return      blueShipButton.isActive()
    +           redShipButton.isActive()
    +           greenShipButton.isActive()
    +           purpleShipButton.isActive();
}
