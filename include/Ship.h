#ifndef SHIP_H
#define SHIP_H
#include "raylib.h"


class Ship {

public:

    float x, y, angle;
    Texture2D redtex, bluetex, greentex, purpletex;

    Ship ();

    /*void control() {

    }

    void draw() {

    }*/
};

#endif // SHIP_H
