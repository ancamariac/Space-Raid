#include "GameScene.h"
#include "box2d/box2d.h"
#include "Constants.h"

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

//b2CircleShape * cs;
b2Body * box;

b2PolygonShape * ps;

b2Body * ship;

b2PolygonShape * shipShape;

Texture2D texShip;

GameScene::GameScene (){

    // Create b2World
    b2Vec2 gravity(0,0);
    world = new b2World(gravity);
    fooDraw = new FooDraw();
    fooDraw->SetFlags( b2Draw ::e_shapeBit );
    world->SetDebugDraw(fooDraw);

    texShip = LoadTexture("assets/blueship.png");


    // Create a box
    b2BodyDef bodyDef;
    bodyDef.position.x = 0;
    bodyDef.position.y = 0;

    box = world->CreateBody(&bodyDef);

    /*
    cs = new b2CircleShape();
    cs->m_radius = 1.f;
    cs->m_p.x = 0;
    cs->m_p.y = 0;
    */

    ps = new b2PolygonShape();
    ps->SetAsBox(5,1);


    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.5f;
    fixtureDef.shape = ps;

    box->CreateFixture(&fixtureDef);


    // create a ship

    bodyDef.position.x = -2;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.angularDamping = 0.9f;
    bodyDef.linearDamping = 0.8f;

    ship = world->CreateBody(&bodyDef);

    b2Vec2 points[3];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = -0.5f;
    points[1].y = +0.3f;
    points[2].x = -0.5f;
    points[2].y = -0.3f;

    shipShape = new b2PolygonShape();
    shipShape->Set(points,3);

    b2FixtureDef shipFixtureDef;
    shipFixtureDef.shape = shipShape;
    shipFixtureDef.friction = 0.5f;
    shipFixtureDef.density = 1.0f;

    ship->CreateFixture(&shipFixtureDef);
}

GameScene::~GameScene()
{
    delete world;
    delete fooDraw;
}


void GameScene::draw () {


    inputController.draw();



    float angle = ship->GetAngle();

    Vector2 origin;
    origin.x = +texShip.width*4 - 4*4;
    origin.y = -texShip.height*2;

    Vector2 pos = { ship->GetPosition().x * scaleFactor+screenWidth/2 // x-ul varfului celui rosu
                    - cos(angle)*origin.x - sin(angle) * origin.y
                    ,
                    ship->GetPosition().y * scaleFactor + screenHeight/2 // y-ul varfului celui rosu
                    - sin(angle)*origin.x + cos(angle) * origin.y
                    };

    //Vector2 pos = {50,50};
    DrawTextureEx(texShip,pos,ship->GetAngle() / 3.14 * 180,4,WHITE);

    world->DebugDraw();

/*
    Vector2 pos = { ship->GetPosition().x * scaleFactor+screenWidth/2
                    + cos(angle)*texShip.width*4/2
                    ,
                    ship->GetPosition().y * scaleFactor + screenHeight/2
                    + sin(angle)*texShip.height*4/2
                    };

    //Vector2 pos = {50,50};
    DrawTextureEx(texShip,pos,ship->GetAngle() / 3.14 * 180 +90,4,WHITE);
*/
}

b2Vec2 pushForce = {7.f,0};
b2Vec2 noForce = {0.f,0};

void GameScene::update () {
    inputController.update();
    world->Step(1.f/60.f, 8, 3);

    //if ( IsMouseButtonDown(MOUSE_LEFT_BUTTON) ){
        float angle = ship->GetAngle();
        ship->ApplyForceToCenter( b2Vec2{cos(angle),sin(angle)}, true );
        //ship->SetLinearVelocity(b2Vec2{cos(angle)*5,sin(angle)*5});
    //}

    if ( IsMouseButtonDown(MOUSE_RIGHT_BUTTON) ){
        //ship->ApplyTorque( 0.05f, true);
        float angle = ship->GetAngle();
        ship->SetTransform(ship->GetPosition(),angle+0.07f);
    }
}

void GameScene::setupScene(){
    inputController.setLayout();
}
