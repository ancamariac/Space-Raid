#ifndef TAPTOSTART_H
#define TAPTOSTART_H
#include "raylib.h"


class TapToStart {
public:
    Texture2D logo, taptostart;

    int mouseX = 0, mouseY = 0;
    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;         // Button action should be activated
    Vector2 mousePoint = { 0.0f, 0.0f };

    TapToStart ();

    void draw();
    void update();

};

#endif // TAPTOSTART_H
