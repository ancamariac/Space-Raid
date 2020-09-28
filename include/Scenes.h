#ifndef SCENES_H
#define SCENES_H

#include "GameScene.h"

enum class Scenes {
TapToStart,
MainMenu,
ChooseColor,
GameScene
};

extern Scenes currentScene;

extern bool playingShips[4];
extern int shipsNumber;

extern GameScene * gameSceneReference;

#endif // SCENES_H
