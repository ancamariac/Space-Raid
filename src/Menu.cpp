#include "Menu.h"
#include "Constants.h"
#include "Helpers.h"
#include "Scenes.h"

Menu::Menu () {

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

void Menu::draw(){

    DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2 - 175, WHITE);
    DrawTextureEx(playgame, playGamePos, 0, 4, WHITE);
    DrawTextureEx(options, optionsPos, 0, 4, WHITE);
    DrawTextureEx(credits, creditsPos, 0, 4, WHITE);

}

void Menu::update() {

    if ( IsRecClicked( MOUSE_LEFT_BUTTON, playGamePos.x, playGamePos.y, playgame.width*4, playgame.height*4 ) ) {
        currentScene = Scenes::ChooseColors;
    }
}
