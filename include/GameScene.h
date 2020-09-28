#ifndef GAMESCENES_H
#define GAMESCENES_H
#include "InputController.h"
#include "Ship.h"

class GameScene {
public :
    GameScene ();
    virtual ~GameScene();

    void draw ();

    void update ();
    void setupScene();
private:
    InputController inputController;
    void spawnShips();
    Ship * ships[4];
};

#endif // GAMESCENES_H
