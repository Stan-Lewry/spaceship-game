#pragma once

#include "Component.h"
#include "../Utils/Types.h"

class PhysicsComponent : public Component {
public:
    PhysicsComponent(vect<vect<float>> boundingBox, std::string name, bool solid);
    virtual ~PhysicsComponent();
    rect<float> getBoundingBox();
    
    vect<float> getVelocity();
    void setVelocity(vect<float> vel);
    std::string getName();
    void addCollision(PhysicsComponent* pc);
    void clearCollisions();
    std::vector<PhysicsComponent*> getCurrnentCollisionList();
    bool isSolid();

private:

    vect<float> velocity;
    vect<vect<float>> boundingBox;
    std::string name;
    std::vector<PhysicsComponent*> currentCollisionList;
    bool solid;
};