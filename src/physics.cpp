#include "physics.h"
#include <box2d/box2d.h>
#include <iostream>

b2World world(b2Vec2(0.0f, -9.8f));  // Gravity
b2Body* playerBody;
GameContactListener contactListener;

void initPhysics() {
    world.SetContactListener(&contactListener); // Register collision detection

    // Create a wall at x = 5
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(5.0f, 0.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(0.5f, 10.0f);  // Thin wall, height=10
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Create the player
    b2BodyDef bodyDef;
    bodyDef.position.Set(0.0f, 0.0f);
    bodyDef.type = b2_dynamicBody;
    playerBody = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(0.5f, 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;  // Increase friction to help prevent sliding through walls
    playerBody->CreateFixture(&fixtureDef);
}

void stepPhysics() {
    // Apply linear damping to slow movement (simulate friction)
    playerBody->SetLinearDamping(2.0f);
    world.Step(1.0f / 60.0f, 6, 2);
}

void movePlayer(const std::string& direction) {
    float force = 5.0f;
    if (direction == "left") {
        playerBody->ApplyForceToCenter(b2Vec2(-force, 0.0f), true);
    } else if (direction == "right") {
        playerBody->ApplyForceToCenter(b2Vec2(force, 0.0f), true);
    }
}
