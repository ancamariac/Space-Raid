#include "Ship.h"

#include "Constants.h"
b2World * gameWorld;
b2CircleShape * shipShape;
b2CircleShape * bulletShape;

Ship::Ship(b2World * world, int type)
{
    gameWorld = world;
    switch( type ) {
    case 1:
        texShip = LoadTexture("assets/blueship.png");
        break;
    case 2:
        texShip = LoadTexture("assets/redship.png");
        break;
    case 3:
        texShip = LoadTexture("assets/greenship.png");
        break;
    case 4:
        texShip = LoadTexture("assets/purpleship.png");
        break;
    }

    // create a box2d ship

    b2BodyDef shipBodyDef;
    shipBodyDef.position.x = -2;
    shipBodyDef.type = b2BodyType::b2_dynamicBody;
    shipBodyDef.angularDamping = 0.9f;
    shipBodyDef.linearDamping = 0.8f;
    shipBodyDef.fixedRotation = true;

    body = world->CreateBody(&shipBodyDef);

    shipShape = new b2CircleShape();
    shipShape->m_radius = 0.2f;

    b2FixtureDef shipFixtureDef;
    shipFixtureDef.shape = shipShape;
    shipFixtureDef.friction = 0.0001f;
    shipFixtureDef.density = 1.0f;

    body->CreateFixture(&shipFixtureDef);
}

Ship::~Ship()
{
    //dtor
}

#include <vector>
std::vector <b2Body*> bullets;

void Ship::update(bool rotateDown, bool shootPressed)
{
    float angle = body->GetAngle();
    body->ApplyForceToCenter( b2Vec2{cos(angle),sin(angle)}, true );
    // body->SetLinearVelocity( b2Vec2{cos(angle)*5,sin(angle)*5} );

    if ( rotateDown ) {
        float angle = body->GetAngle();
        body->SetTransform(body->GetPosition(),angle + 0.07f);
    }

    // TO DO: Create bullets
    if ( shootPressed ) {
        // trage gloante
        b2BodyDef bulletBodyDef;
        bulletBodyDef.position.x = body->GetPosition().x + cos(body->GetAngle());
        bulletBodyDef.position.y = body->GetPosition().y + sin(body->GetAngle());
        bulletBodyDef.type = b2BodyType::b2_dynamicBody;
        bulletBodyDef.angularDamping = 0.9f;
        bulletBodyDef.linearDamping = 0.0001f;
        bulletBodyDef.bullet = true;
        bulletBodyDef.linearVelocity = b2Vec2{cos(body->GetAngle()) * 10, sin(body->GetAngle()) * 10};
        //shipBodyDef.fixedRotation = true;

        b2Body * bulletBody = gameWorld->CreateBody(&bulletBodyDef);

        bulletShape = new b2CircleShape();
        bulletShape->m_radius = 0.1f;

        b2FixtureDef bulletFixtureDef;
        bulletFixtureDef.shape = bulletShape;
        bulletFixtureDef.friction = 0.0001f;
        bulletFixtureDef.density = 1.0f;

        bulletBody->CreateFixture(&bulletFixtureDef);
        bullets.push_back(bulletBody);
    }

    //DEBUG
    if ( IsKeyPressed(KEY_R) ){
        body->SetTransform(body->GetPosition(),0);
    }
}

void Ship::draw()
{
    float angle = body->GetAngle();

    Vector2 origin;
    origin.x = +texShip.width * 4 - 6 * 4;
    origin.y = -texShip.height * 2 - 2 ;

    Vector2 pos = { body->GetPosition().x * scaleFactor + screenWidth / 2 // yellow circle x
                    - cos(angle)*origin.x - sin(angle) * origin.y
                    ,
                    body->GetPosition().y * scaleFactor + screenHeight/2  // yellow circle y
                    - sin(angle)*origin.x + cos(angle) * origin.y
                    };

    DrawTextureEx(texShip,pos, angle / 3.14 * 180, 4, WHITE);

    // DEBUG
    DrawLine(body->GetPosition().x * scaleFactor + screenWidth / 2,
             body->GetPosition().y * scaleFactor + screenHeight/2,

             body->GetPosition().x * scaleFactor + screenWidth / 2
             + cos(body->GetAngle()) * 500,
             body->GetPosition().y * scaleFactor + screenHeight/2
             + sin(body->GetAngle()) * 500,

             RED
             );

    b2Vec2 velocity = body->GetLinearVelocity();
    // DEBUG
    DrawLine(body->GetPosition().x * scaleFactor + screenWidth / 2,
             body->GetPosition().y * scaleFactor + screenHeight/2,

             body->GetPosition().x * scaleFactor + screenWidth / 2
             + velocity.x * 50,
             body->GetPosition().y * scaleFactor + screenHeight/2
             + velocity.y * 50,

             GREEN
             );
    for ( std::vector<b2Body*>::iterator it = bullets.begin(); it != bullets.end(); it++ ){

    b2Body * testBody = *it;
    b2Vec2 velo = testBody->GetLinearVelocity();
    DrawLine(testBody->GetPosition().x * scaleFactor + screenWidth / 2,
             testBody->GetPosition().y * scaleFactor + screenHeight/2,

             testBody->GetPosition().x * scaleFactor + screenWidth / 2
             + velo.x * 10,
             testBody->GetPosition().y * scaleFactor + screenHeight/2
             + velo.y * 10,

             GREEN
             );

    }
}

b2Body* Ship::getBody()
{
    return body;
}
