#include "Menu.h"
#include "Constants.h"
#include "Helpers.h"
#include "Scenes.h"

Menu::Menu () {

    logo = LoadTexture("assets/logov2.png");       // asset for logo button
    credits = LoadTexture("assets/credits.png");   // asset for credits button
    options = LoadTexture("assets/options.png");   // asset for options button
    playgame = LoadTexture("assets/playgame.png"); // asset for play game button

    // set the positions for each button using Vector2
    playGamePos.x = screenWidth / 2 - playgame.width * 4;
    playGamePos.y = screenHeight / 2 - playgame.height * 4 + 250;
    optionsPos.x  = screenWidth / 2 - options.width * 4 - 200;
    optionsPos.y  = screenHeight / 2 - options.height * 4 + 400;
    creditsPos.x  = screenWidth / 2 - credits.width * 4 + 180;
    creditsPos.y  = screenHeight / 2 - credits.height * 4 + 400;
}

void Menu::draw(){

    // draw buttons using the positions given by Vector2
    DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2 - 175, WHITE);
    DrawTextureEx(playgame, playGamePos, 0, 8, WHITE);
    DrawTextureEx(options, optionsPos, 0, 8, WHITE);
    DrawTextureEx(credits, creditsPos, 0, 8, WHITE);
}

void Menu::update() {

    // check if the Play Game button is pressed
    if ( IsRecClicked( MOUSE_LEFT_BUTTON,
         playGamePos.x, playGamePos.y, playgame.width * 8, playgame.height * 8 ) ) {
        // move to the next scene
        currentScene = Scenes::ChooseColor;
    }
}
