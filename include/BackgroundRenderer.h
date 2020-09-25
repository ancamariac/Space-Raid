#ifndef BACKGROUNDRENDERER_H
#define BACKGROUNDRENDERER_H
#include "raylib.h"

class BackgroundRenderer {
public:
    Texture2D background;
    float scrollingBack = 0.0f;
    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;         // Button action should be activated
    Vector2 mousePoint = { 0.0f, 0.0f };

    BackgroundRenderer ();

    void draw();
};


#endif // BACKGROUNDRENDERER_H
