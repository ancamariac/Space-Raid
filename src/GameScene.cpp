#include "GameScene.h"

    GameScene::GameScene (){}

    void GameScene::draw () {
        inputController.draw();
    }

    void GameScene::update () {
        inputController.update();
    }

    void GameScene::setupScene(){
        inputController.setLayout();
    }
