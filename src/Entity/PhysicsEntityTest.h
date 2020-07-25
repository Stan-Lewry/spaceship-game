#pragma once

#include "Entity.h"
#include "../Component/WorldComponent.h"
#include "../Component/PhysicsComponent.h"
#include "../Component/InputComponent.h"

class PhysicsEntityTest : public Entity {
public:
    PhysicsEntityTest(WorldComponent* wc, PhysicsComponent* pc, InputComponent* ic);
    virtual ~PhysicsEntityTest();
protected:
    void doUpdate() override;
private:
    WorldComponent* worldComponent;
    PhysicsComponent* physicsComponent;
    InputComponent* inputComponent;  
};