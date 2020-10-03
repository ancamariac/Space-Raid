#ifndef CHOOSECOLORBUTTON_H
#define CHOOSECOLORBUTTON_H
#include "raylib.h"

class ChooseColorButton {

private:
    void setNumber( int n );
    void setPosition( int _x , int _y );
    bool active = false;

public:
    int x = 0, y = 0;
    const int width = 200;
    const int height = 100;
    Texture2D shipTex, offTex;
    Vector2 buttonPos;

    void configure( int _x, int _y, int color );
    void draw();
    void update();
    bool isActive();
};

#endif // CHOOSECOLORBUTTON_H
