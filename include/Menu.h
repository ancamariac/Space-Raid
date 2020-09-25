#ifndef MENU_H
#define MENU_H
#include "raylib.h"


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

    Menu();

    void draw();

    void update();
};
#endif // MENU_H
