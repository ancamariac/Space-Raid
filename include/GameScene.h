#ifndef GAMESCENES_H
#define GAMESCENES_H
#include "InputController.h"

class GameScene {
public :
    GameScene ();

    void draw ();

    void update ();
private:
    InputController inputController;
};

#endif // GAMESCENES_H
