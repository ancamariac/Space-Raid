#include "GameScene.h"
#include "box2d/box2d.h"
#include "Constants.h"
#include "Ship.h"

#include "Scenes.h"

b2World * world;

// this stuff helps the compiler in order to avoiding the conflicts between 2 functions with the same name
void raylibDrawCircle(float x, float y, float radius, Color color){
    DrawCircle(x, y, radius, color);
}

#include <iostream>
using namespace std;

class FooDraw : public b2Draw  {
  public:
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

    }
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

        for ( int i = 0; i < vertexCount - 1; i++ ) {

            // set the Box2D World origin in the middle of the screen
            DrawLine(vertices[i].x * scaleFactor + screenWidth / 2,
                     vertices[i].y * scaleFactor + screenHeight / 2,
                     vertices[i + 1].x * scaleFactor + screenWidth / 2,
                     vertices[i + 1].y * scaleFactor+screenHeight / 2, RED);
        }

            DrawLine(vertices[0].x * scaleFactor + screenWidth / 2,
                     vertices[0].y * scaleFactor + screenHeight / 2,
                     vertices[vertexCount - 1].x * scaleFactor + screenWidth / 2,
                     vertices[vertexCount - 1].y * scaleFactor + screenHeight / 2, RED);

    }

    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {}

    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
        raylibDrawCircle((center.x) * scaleFactor + screenWidth / 2,
                         (center.y) * scaleFactor + screenHeight / 2,
                         radius * scaleFactor,YELLOW);
    }
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
    void DrawTransform(const b2Transform& xf) {}
	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) {};
};

FooDraw * fooDraw;

b2Body * box;

b2PolygonShape * ps1;
b2PolygonShape * ps2;
b2PolygonShape * ps3;
b2PolygonShape * ps4;

//Ship * ship;

GameScene::GameScene (){

    // Create b2World
    b2Vec2 gravity(0,0);
    world = new b2World(gravity);
    fooDraw = new FooDraw();
    fooDraw->SetFlags( b2Draw ::e_shapeBit );
    world->SetDebugDraw(fooDraw);

    // Create a border

    // horizontal up
    b2BodyDef up;
    up.position.x = 0;
    up.position.y = -9.9;

    box = world->CreateBody(&up);

    ps1 = new b2PolygonShape();
    ps1->SetAsBox(8,0.1);


    b2FixtureDef fixtureUp;
    fixtureUp.density = 1.f;
    fixtureUp.friction = 0.0001f;
    fixtureUp.shape = ps1;

    box->CreateFixture(&fixtureUp);

    // horizontal down
    b2BodyDef down;
    down.position.x = 0;
    down.position.y = 9.9;

    box = world->CreateBody(&down);

    ps2 = new b2PolygonShape();
    ps2->SetAsBox(8,0.1);


    b2FixtureDef fixtureDown;
    fixtureDown.density = 1.f;
    fixtureDown.friction = 0.0001f;
    fixtureDown.shape = ps2;

    box->CreateFixture(&fixtureDown);

    // vertical left
    b2BodyDef left;
    left.position.x = -8;
    left.position.y = 0;

    box = world->CreateBody(&left);

    ps3 = new b2PolygonShape();
    ps3->SetAsBox(0.1, 10);


    b2FixtureDef fixtureLeft;
    fixtureLeft.density = 1.f;
    fixtureLeft.friction = 0.0001f;
    fixtureLeft.shape = ps3;

    box->CreateFixture(&fixtureLeft);

    // vertical right
    b2BodyDef right;
    right.position.x = 8;
    right.position.y = 0;

    box = world->CreateBody(&right);

    ps4 = new b2PolygonShape();
    ps4->SetAsBox(0.1, 10);


    b2FixtureDef fixtureRight;
    fixtureRight.density = 1.f;
    fixtureRight.friction = 0.0001f;
    fixtureRight.shape = ps4;

    box->CreateFixture(&fixtureRight);


    // Create a ship
    //ship = new Ship(world, 1);
}

GameScene::~GameScene() {
    delete world;
    delete fooDraw;
}


void GameScene::draw () {
    inputController.draw();
    for ( int i = 0; i < 4; i++ ){
        if( ships[i] ){
            ships[i]->draw();
        }
    }

    world->DebugDraw();
}

void GameScene::update () {
    inputController.update();
    world->Step(1.f/60.f, 8, 3);
    for ( int i = 0; i < 4; i++ ){
        if( ships[i] ){
            ships[i]->update( inputController.shouldRotate(i + 1), inputController.shouldShoot(i + 1) );
        }
    }
    //ship->update(IsMouseButtonDown(MOUSE_RIGHT_BUTTON), IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

void GameScene::setupScene(){
    inputController.setLayout();
    spawnShips();
}

void GameScene::spawnShips()
{
    for ( int i = 0; i < 4; i++ ){
        if ( playingShips[i] ) { // extern bool playingShips[4];
            ships[i] = new Ship(world, i + 1);

            // TODO : replace this with actual spawn locations
            b2Body * b = ships[i]->getBody();
            b2Vec2 pos = b->GetPosition();
            pos.x += i;
            b->SetTransform(pos,b->GetAngle());
        } else {
            ships[i] = nullptr;
        }
    }
}
