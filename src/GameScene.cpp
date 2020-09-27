#include "GameScene.h"
#include "box2d/box2d.h"
#include "Constants.h"
#include "Ship.h"

b2World * world;

// this stuff helps the compiler in order to avoiding the conflicts between 2 functions with the same name
void raylibDrawCircle(float x, float y, float radius, Color color){
    DrawCircle(x,y,radius,color);
}

#include <iostream>
using namespace std;

class FooDraw : public b2Draw  {
  public:
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

    }
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {


        /*
        DrawLine(vertices[0].x*scaleFactor,vertices[0].y*scaleFactor,vertices[1].x*scaleFactor,vertices[1].y*scaleFactor,RED);
        DrawLine(vertices[1].x*scaleFactor,vertices[1].y*scaleFactor,vertices[2].x*scaleFactor,vertices[2].y*scaleFactor,RED);
        DrawLine(vertices[0].x*scaleFactor,vertices[0].y*scaleFactor,vertices[2].x*scaleFactor,vertices[2].y*scaleFactor,RED);
        */

        for ( int i = 0; i < vertexCount-1; i++)
        {
            DrawLine(vertices[i].x*scaleFactor+screenWidth/2,
                     vertices[i].y*scaleFactor+screenHeight/2,
                     vertices[i+1].x*scaleFactor+screenWidth/2,
                     vertices[i+1].y*scaleFactor+screenHeight/2, RED);
        }

            DrawLine(vertices[0].x*scaleFactor+screenWidth/2,
                     vertices[0].y*scaleFactor+screenHeight/2,
                     vertices[vertexCount-1].x*scaleFactor+screenWidth/2,
                     vertices[vertexCount-1].y*scaleFactor+screenHeight/2, RED);

        //cout << vertexCount << endl;
    }
    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    }
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
        raylibDrawCircle((center.x)*scaleFactor + screenWidth/2,
                         (center.y)*scaleFactor + screenHeight/2,
                         radius*scaleFactor,YELLOW);
    }
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
    void DrawTransform(const b2Transform& xf) {}
	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) {};
};

FooDraw * fooDraw;

b2Body * box;

b2PolygonShape * ps;

Ship * ship;

GameScene::GameScene (){

    // Create b2World
    b2Vec2 gravity(0,0);
    world = new b2World(gravity);
    fooDraw = new FooDraw();
    fooDraw->SetFlags( b2Draw ::e_shapeBit );
    world->SetDebugDraw(fooDraw);

    // Create a box
    b2BodyDef bodyDef;
    bodyDef.position.x = 0;
    bodyDef.position.y = 0;

    box = world->CreateBody(&bodyDef);

    ps = new b2PolygonShape();
    ps->SetAsBox(5,1);


    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.0001f;
    fixtureDef.shape = ps;

    box->CreateFixture(&fixtureDef);

    // Create a ship
    ship = new Ship(world);
}

GameScene::~GameScene()
{
    delete world;
    delete fooDraw;
}


void GameScene::draw () {
    inputController.draw();
    ship->draw();
    world->DebugDraw();
}

b2Vec2 pushForce = {7.f,0};

void GameScene::update () {
    inputController.update();
    world->Step(1.f/60.f, 8, 3);
    ship->update(IsMouseButtonDown(MOUSE_RIGHT_BUTTON), IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

void GameScene::setupScene(){
    inputController.setLayout();
}
