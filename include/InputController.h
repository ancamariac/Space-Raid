#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <vector>
#include "raylib.h"

#define CLICKABLE_TRIANGLE_COUNT 4

class ClickableTriangle {
public:
    ClickableTriangle( Vector2 p1, Vector2 p2, Vector2 p3, Color color );
    void draw();
    void update();
    bool isActive();
private:
    bool active = false;
    Color baseColor, alphaColor;
    Vector2 p1, p2, p3;
};

class InputController
{
    public:

        InputController();
        virtual ~InputController();
        void setLayout();
        void update ();
        void draw ();

    protected:

    private:
        int layout = 2;
        ClickableTriangle* triangles[CLICKABLE_TRIANGLE_COUNT];
};

#endif // INPUTCONTROLLER_H
