#include "Scene.h"

Scene::Scene()
{
    //ctor
}

Scene::~Scene()
{
    //dtor
}

void Scene::draw(){
    // Iterate through all drawables and ->draw() each.
    for(std::vector<Drawable*>::iterator it = drawables.begin(); it != drawables.end(); ++it) {
        (*it)->draw();
    }
}

void Scene::update(){
    // Iterate through all updateables and ->update() each.
    for(std::vector<Updateable*>::iterator it = updateables.begin(); it != updateables.end(); ++it) {
        (*it)->update();
    }
}

void Scene::addDrawable(Drawable* d){
    drawables.push_back(d);
}

void Scene::addUpdateable(Updateable* u) {
    updateables.push_back(u);
}
