#include "ChooseColorButton.h"
#include "raylib.h"
#include "Helpers.h"

const int CCBscale = 14; // choose color button scale

void ChooseColorButton::setNumber( int n ){
    switch ( n ) {

        case 1:
            shipTex = LoadTexture("assets/bluebutton.png");
            break;
        case 2:
            shipTex = LoadTexture("assets/redbutton.png");
            break;
        case 3 :
            shipTex = LoadTexture("assets/greenbutton.png");
            break;
        case 4:
            shipTex = LoadTexture("assets/purplebutton.png");
            break;
    }

    offTex = LoadTexture("assets/offbutton.png");
}

void ChooseColorButton::setPosition( int _x , int _y ){
    x = _x;
    y = _y;
    buttonPos.x = x;
    buttonPos.y = y;
}

void ChooseColorButton::configure( int _x, int _y, int color ) {
    setPosition(_x,_y);
    setNumber(color);
}

void ChooseColorButton::draw() {
    if ( active ){
        // Draw  off button
        DrawTextureEx(shipTex, buttonPos, 0, CCBscale, WHITE);
    } else {
        // Draw off button
        DrawTextureEx(offTex, buttonPos, 0, CCBscale, WHITE);
    }
}

void ChooseColorButton::update() {
    if ( IsRecClicked( MOUSE_LEFT_BUTTON, x, y,
                      shipTex.width * CCBscale, shipTex.height * CCBscale ) ) {
        active = !active;
    }
}

bool ChooseColorButton::isActive() {
    return active;
}


