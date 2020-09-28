#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <vector>
#include "raylib.h"

class ClickableTriangle {
public:
    ClickableTriangle( Vector2 p1, Vector2 p2, Vector2 p3, Color color );
    void draw();
    void update();
    bool isDown();
    bool isJustPressed();
private:
    bool down = false;
    bool justPressed = false;
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

        bool shouldRotate( int ship );
        bool shouldShoot ( int ship );

    protected:

    private:
        int layout = 2;
        std::vector<ClickableTriangle*> triangles;
        ClickableTriangle * shipRotateButtons[5];
        ClickableTriangle * shipShootButtons[5];
        void initWithZero();
};

#endif // INPUTCONTROLLER_H
