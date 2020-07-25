#pragma once

#include "Entity.h"
#include "../Component/WorldComponent.h"
#include "../Component/PhysicsComponent.h"

class SimpleWorldEntity : public Entity {
public:
    SimpleWorldEntity(WorldComponent* wc, PhysicsComponent* pc);
    virtual ~SimpleWorldEntity();
protected:
    void doUpdate() override;
private:
    WorldComponent* worldComponent;
    PhysicsComponent* physicsComponent;
};