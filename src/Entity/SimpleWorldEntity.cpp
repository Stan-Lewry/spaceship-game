#include "SimpleWorldEntity.h"

SimpleWorldEntity::SimpleWorldEntity(WorldComponent* wc, PhysicsComponent* pc)
    : Entity(-1)
    , worldComponent(wc)
    , physicsComponent(pc) {}

SimpleWorldEntity::~SimpleWorldEntity() {}

void SimpleWorldEntity::doUpdate() {}