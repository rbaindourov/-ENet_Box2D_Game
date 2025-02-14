#ifndef PHYSICS_H
#define PHYSICS_H

#include <box2d/box2d.h>
#include <string>
#include <iostream>

class GameContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override {
        std::cout << "Collision detected!" << std::endl;
    }
    void EndContact(b2Contact* contact) override {
        std::cout << "Collision ended!" << std::endl;
    }
};

extern b2World world;
extern b2Body* playerBody;

void initPhysics();
void stepPhysics();
void movePlayer(const std::string& direction);

#endif
