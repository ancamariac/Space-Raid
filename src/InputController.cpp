#include "InputController.h"
#include "raylib.h"
#include "Constants.h"
#include "Helpers.h"
#include "Scenes.h"

ClickableTriangle::ClickableTriangle(Vector2 _p1, Vector2 _p2, Vector2 _p3, Color color) {

    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    baseColor = color;
    alphaColor = baseColor;
    alphaColor.a = 127;
}

void ClickableTriangle::draw()
{
    if ( down ) {
        DrawTriangle(p1, p2, p3, baseColor);
    } else {
        DrawTriangle(p1, p2, p3, alphaColor);
    }
}

void ClickableTriangle::update()
{
    bool lastFrame = down;
    down = false;

    // Replace logic to work with touch
    if ( IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if ( IsPointInTriangle(mousePos, p1, p2, p3) ){
            down = true;
        }
    }

    if ( lastFrame == false && down == true ){
        justPressed = true;
    } else {
        justPressed = false;
    }
}

bool ClickableTriangle::isDown()
{
    return down;
}

bool ClickableTriangle::isJustPressed()
{
    return justPressed;
}


InputController::InputController()
{

}

InputController::~InputController()
{
    // TODO : destroy layout triangles when the scene is popped off the stack.
    for ( std::vector<ClickableTriangle*>::iterator it = triangles.begin(); it != triangles.end(); it++ ){
        delete (*it);
    }
}

Color getShipColor ( int index ){ // 1-based
    switch(index){
    case 1:
        return BLUE;
        break;
    case 2:
        return RED;
        break;
    case 3:
        return GREEN;
        break;
    case 4:
        return PURPLE;
        break;
    }
    return BLACK;
}

Color getColorOfControllerPair(int index) { // 1-based
    for ( int i = 0; i < 4; i++ ){
        if (playingShips[i])
            index--;
        if ( index == 0 )
            return getShipColor(i+1);
    }
    return BLACK;
}

// TODO : rewrite getColorOfControllerPair to use getControllerPairShipIndex internally
int getControllerPairShipIndex(int index) { // 1-based
    for ( int i = 0; i < 4; i++ ){
        if (playingShips[i])
            index--;
        if ( index == 0 )
            return i + 1;
    }
    return -1;
}

bool InputController::shouldRotate(int ship) // 1/2/3/4
{
    return shipRotateButtons[ship]->isDown();
}

bool InputController::shouldShoot(int ship) // 1/2/3/4
{
    return shipShootButtons[ship]->isJustPressed();
}

void InputController::initWithZero()
{
    for ( int i = 0; i < 4; i++ ){
        shipRotateButtons[i] = nullptr;
        shipShootButtons[i]  = nullptr;
    }
}


// Function called when the GameScene becomes active ( one time )
// Creates the layout for the input controller depending on how many players play
void InputController::setLayout()
{
    initWithZero();
    layout = shipsNumber;

    switch(layout) {
        case 2:
            // dreapta invarte, stanga trage
            shipShootButtons[getControllerPairShipIndex(1)] = new ClickableTriangle(Vector2{0,0},
                                                      Vector2{0, 400},
                                                      Vector2{400, 0},
                                                      getColorOfControllerPair(1));

            shipRotateButtons[getControllerPairShipIndex(1)] = new ClickableTriangle(Vector2{0, screenHeight},
                                                      Vector2{400, screenHeight},
                                                      Vector2{0, screenHeight - 400},
                                                      getColorOfControllerPair(1));

            shipRotateButtons[getControllerPairShipIndex(2)] = new ClickableTriangle(Vector2{screenWidth, 400},
                                                      Vector2{screenWidth,0},
                                                      Vector2{screenWidth - 400, 0},
                                                      getColorOfControllerPair(2));

            shipShootButtons[getControllerPairShipIndex(2)] = new ClickableTriangle(Vector2{screenWidth - 400, screenHeight},
                                                      Vector2{screenWidth, screenHeight},
                                                      Vector2{screenWidth, screenHeight - 400},
                                                      getColorOfControllerPair(2));

            triangles.push_back(shipShootButtons[getControllerPairShipIndex(1)]);
            triangles.push_back(shipShootButtons[getControllerPairShipIndex(2)]);
            triangles.push_back(shipRotateButtons[getControllerPairShipIndex(1)]);
            triangles.push_back(shipRotateButtons[getControllerPairShipIndex(2)]);
            break;

        case 3:
            // Counter Clock Wise - CCW

            // First pair
            shipShootButtons[getControllerPairShipIndex(1)] = new ClickableTriangle(Vector2{0, 0},
                                                      Vector2{180, 180},
                                                      Vector2{400, 0},
                                                      getColorOfControllerPair(1));

            shipRotateButtons[getControllerPairShipIndex(1)] = new ClickableTriangle(Vector2{0, 0},
                                                      Vector2{0, 400},
                                                      Vector2{180, 180},
                                                      getColorOfControllerPair(1));

            // Second pair
            shipRotateButtons[getControllerPairShipIndex(2)] = new ClickableTriangle(Vector2{screenWidth, 0},
                                                      Vector2{screenWidth - 400, 0},
                                                      Vector2{screenWidth - 180, 180},
                                                      getColorOfControllerPair(2));

            shipShootButtons[getControllerPairShipIndex(2)] = new ClickableTriangle(Vector2{screenWidth, 0},
                                                      Vector2{screenWidth - 180, 180},
                                                      Vector2{screenWidth, 400},
                                                      getColorOfControllerPair(2));

            // Third pair
            shipRotateButtons[getControllerPairShipIndex(3)] = new ClickableTriangle(Vector2{screenWidth, screenHeight - 400},
                                                      Vector2{screenWidth - 180, screenHeight - 180},
                                                      Vector2{screenWidth, screenHeight},
                                                      getColorOfControllerPair(3));

            shipShootButtons[getControllerPairShipIndex(3)] = new ClickableTriangle(Vector2{screenWidth - 400, screenHeight},
                                                      Vector2{screenWidth, screenHeight},
                                                      Vector2{screenWidth - 180, screenHeight - 180},
                                                      getColorOfControllerPair(3));

            triangles.push_back(shipShootButtons[getControllerPairShipIndex(1)]);
            triangles.push_back(shipShootButtons[getControllerPairShipIndex(2)]);
            triangles.push_back(shipShootButtons[getControllerPairShipIndex(3)]);
            triangles.push_back(shipRotateButtons[getControllerPairShipIndex(1)]);
            triangles.push_back(shipRotateButtons[getControllerPairShipIndex(2)]);
            triangles.push_back(shipRotateButtons[getControllerPairShipIndex(3)]);
            break;
        case 4:
            // First pair
            shipShootButtons[getControllerPairShipIndex(1)] = new ClickableTriangle(Vector2{0, 0},
                                                      Vector2{180, 180},
                                                      Vector2{400, 0},
                                                      getColorOfControllerPair(1));

            shipRotateButtons[getControllerPairShipIndex(1)] = new ClickableTriangle(Vector2{0, 0},
                                                      Vector2{0, 400},
                                                      Vector2{180, 180},
                                                      getColorOfControllerPair(1));

            // Second pair
            shipRotateButtons[getControllerPairShipIndex(2)] = new ClickableTriangle(Vector2{screenWidth, 0},
                                                      Vector2{screenWidth - 400, 0},
                                                      Vector2{screenWidth - 180, 180},
                                                      getColorOfControllerPair(2));

            shipShootButtons[getControllerPairShipIndex(2)] = new ClickableTriangle(Vector2{screenWidth, 0},
                                                      Vector2{screenWidth - 180, 180},
                                                      Vector2{screenWidth, 400},
                                                      getColorOfControllerPair(2));

            // Third pair
            shipRotateButtons[getControllerPairShipIndex(3)] = new ClickableTriangle(Vector2{screenWidth, screenHeight - 400},
                                                      Vector2{screenWidth - 180, screenHeight - 180},
                                                      Vector2{screenWidth, screenHeight},
                                                      getColorOfControllerPair(3));

            shipShootButtons[getControllerPairShipIndex(3)] = new ClickableTriangle(Vector2{screenWidth - 400, screenHeight},
                                                      Vector2{screenWidth, screenHeight},
                                                      Vector2{screenWidth - 180, screenHeight - 180},
                                                      getColorOfControllerPair(3));

            // Fourth pair
            shipShootButtons[getControllerPairShipIndex(4)] = new ClickableTriangle(Vector2{0, screenHeight},
                                                      Vector2{180, screenHeight - 180},
                                                      Vector2{0, screenHeight - 400},
                                                      getColorOfControllerPair(4));

            shipRotateButtons[getControllerPairShipIndex(4)] = new ClickableTriangle(Vector2{180, screenHeight - 180},
                                                      Vector2{0, screenHeight},
                                                      Vector2{400, screenHeight},
                                                      getColorOfControllerPair(4));

            triangles.push_back(shipShootButtons[getControllerPairShipIndex(1)]);
            triangles.push_back(shipShootButtons[getControllerPairShipIndex(2)]);
            triangles.push_back(shipShootButtons[getControllerPairShipIndex(3)]);
            triangles.push_back(shipShootButtons[getControllerPairShipIndex(4)]);
            triangles.push_back(shipRotateButtons[getControllerPairShipIndex(1)]);
            triangles.push_back(shipRotateButtons[getControllerPairShipIndex(2)]);
            triangles.push_back(shipRotateButtons[getControllerPairShipIndex(3)]);
            triangles.push_back(shipRotateButtons[getControllerPairShipIndex(4)]);
            break;
    }

}

void InputController::update()
{
    // Iterate through the triangles vector and update them
    for ( std::vector<ClickableTriangle*>::iterator it = triangles.begin(); it != triangles.end(); it++ ){
        (*it)->update();
    }


}


void InputController::draw()
{
    // Iterate through the triangles vector and draw them
    for ( std::vector<ClickableTriangle*>::iterator it = triangles.begin(); it != triangles.end(); it++ ){
        (*it)->draw();
    }
}
