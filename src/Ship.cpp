#include "Ship.h"

Ship::Ship (){
        x = 0;
        y = 0;
        angle = 0;
        redtex = LoadTexture("assets/redship.png");
        bluetex = LoadTexture("assets/blueship.png");
        greentex = LoadTexture("assets/greenship.png");
        purpletex = LoadTexture("assets/purpleship.png");
    }

    /*void Ship::control() {

    }

    void Ship::draw() {

    }*/
