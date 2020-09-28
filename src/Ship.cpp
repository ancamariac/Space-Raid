#include "Ship.h"

#include "Constants.h"

b2CircleShape * shipShape;

Ship::Ship(b2World * world)
{
    texShip = LoadTexture("assets/blueship.png");

    // create a box2d ship

    b2BodyDef bodyDef;
    bodyDef.position.x = -2;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.angularDamping = 0.9f;
    bodyDef.linearDamping = 0.8f;
    bodyDef.fixedRotation = true;

    body = world->CreateBody(&bodyDef);

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

void Ship::update(bool rotateDown, bool shootPressed)
{
    float angle = body->GetAngle();
    body->ApplyForceToCenter( b2Vec2{cos(angle),sin(angle)}, true );

    if ( rotateDown ) {
        float angle = body->GetAngle();
        body->SetTransform(body->GetPosition(),angle + 0.07f);
    }

    // TO DO: Create bullets
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
}

b2Body* Ship::getBody()
{

}
