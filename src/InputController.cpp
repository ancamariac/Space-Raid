#include "InputController.h"
#include "raylib.h"
#include "Constants.h"

InputController::InputController()
{
    //ctor
}

InputController::~InputController()
{
    //dtor
}

void InputController::setLayout()
{

}

void InputController::update()
{

}


void InputController::draw()
{
    switch ( layout ) {

        case 2:
            DrawTriangle(Vector2{0,0}, Vector2{0, screenHeight/2 - 100}, Vector2{screenWidth/2 - 300, 0}, Color {20, 200, 0, 127});
            DrawTriangle(Vector2{0, screenHeight}, Vector2{screenWidth/2 - 300, screenHeight}, Vector2{0, screenHeight/2 + 100}, Color {20, 200, 0, 127});
            //DrawTriangle(Vector2{screenWidth, 0}, Vector2{});
        break;

        case 3:

        break;

        case 4:
        break;
    }
}
