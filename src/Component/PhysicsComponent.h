#pragma once

#include <string>

#include "Component.h"
#include "../Utils/Types.h"

class PhysicsComponent : public Component {
public:
    PhysicsComponent(vect<vect<float>> boundingBox, uint8_t id, bool solid, bool friction);
    PhysicsComponent(vect<vect<float>> boundingBox, uint8_t id, bool solid);
    virtual ~PhysicsComponent();

    typedef std::vector<uint8_t> PhysicsIdVector;

    rect<float> getBoundingBox();    
    vect<float> getVelocity();
    void setVelocity(vect<float> vel);
    std::string getName();
    uint8_t getId();
    void addCollision(PhysicsComponent* pc);
    void clearCollisions();
    std::vector<PhysicsComponent*> getCurrnentCollisionList();
    bool isSolid();
    bool hasFriction();
    void blacklistPhysics(uint8_t id);
    PhysicsIdVector getPhysicsBlackList();

private:

    vect<float> velocity;
    vect<vect<float>> boundingBox;
    std::string name;
    uint8_t id;
    PhysicsIdVector physicsBlackList;
    std::vector<PhysicsComponent*> currentCollisionList;
    bool solid;
    bool friction;
};