#ifndef SHIP_H
#define SHIP_H

#include "box2d/box2d.h"
#include "raylib.h"

class Ship
{
    public:
        Ship(b2World * world);
        virtual ~Ship();

        void update( bool rotateDown, bool shootPressed );
        void draw();
        b2Body * getBody();

    protected:

    private:
        b2Body * body;
        Texture2D texShip;
};

#endif // SHIP_H
