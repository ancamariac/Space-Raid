#include "ChooseColorButton.h"
#include "raylib.h"

void ChooseColorButton::setNumber( int n ){
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

void ChooseColorButton::setPosition( int _x , int _y ){
    x = _x;
    y = _y;
}

void ChooseColorButton::configure( int _x, int _y, int color ) {
    setPosition(_x,_y);
    setNumber(color);
}

void ChooseColorButton::draw() {
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

void ChooseColorButton::update() {
    if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ){
        Vector2 mousePos = GetMousePosition();

        if ( mousePos.x >= x && mousePos.x <= x + width &&
             mousePos.y >= y && mousePos.y <= y + height
            )
        active = !active;
    }
}

bool ChooseColorButton::isActive() {
    return active;
}


