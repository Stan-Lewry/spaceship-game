#pragma once

#include "../../Utils/SDLUtils.h"

#include "../SubSystem.h"
#include "../../Component/WorldComponent.h"
#include "../../Component/PhysicsComponent.h"

#include <list>

class PhysicsSubSystem : public SubSystem {
public:
    PhysicsSubSystem();
    virtual ~PhysicsSubSystem();
    
    void registerPhysics(WorldComponent* worldCompo, PhysicsComponent* physicsCompo);
    void deRegisterPhysics(WorldComponent* worldCompo, PhysicsComponent* physicsCompo);
    void deRegisterPhysics(PhysicsComponent* physicsCompo);
protected:
    void doUpdate(double dTime) override;
private:
    bool detectCollision(std::pair<WorldComponent*, PhysicsComponent*> entity, vect<float>& velocity);
    void resolveCollisionsAABB(std::pair<WorldComponent*, PhysicsComponent*> entity);
    void resolveFriction(std::pair<WorldComponent*, PhysicsComponent*> entity);

    std::list<std::pair<WorldComponent*, PhysicsComponent*>> physicsComponents;
};