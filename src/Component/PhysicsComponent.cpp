#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(vect<vect<float>> _boundingBox, uint8_t _id, bool _solid)
    : PhysicsComponent(_boundingBox, _id, _solid, true)
{}

PhysicsComponent::PhysicsComponent(vect<vect<float>> _boundingBox, uint8_t _id, bool _solid, bool _friction)
    : boundingBox(_boundingBox)
    , velocity({0, 0})
    , name("")
    , id(_id)
    , physicsBlackList()
    , currentCollisionList()
    , solid(_solid)
    , friction(_friction)
{}

PhysicsComponent::~PhysicsComponent() {
    SDEBUG("destructing physics component");
}

rect<float> PhysicsComponent::getBoundingBox() {
    return {boundingBox.x.x, boundingBox.x.y, boundingBox.y.x - boundingBox.x.x, boundingBox.y.y - boundingBox.x.y};
}

vect<float> PhysicsComponent::getVelocity() {
    return velocity;
}

void PhysicsComponent::setVelocity(vect<float> vel) {
    velocity = vel;
}

std::string PhysicsComponent::getName() {
    return name;
}

uint8_t PhysicsComponent::getId() {
    return id;
}

void PhysicsComponent::addCollision(PhysicsComponent* pc) {
    currentCollisionList.push_back(pc);
}

void PhysicsComponent::clearCollisions() {
    currentCollisionList.clear();
}

std::vector<PhysicsComponent*> PhysicsComponent::getCurrnentCollisionList() {
    return currentCollisionList;
}

bool PhysicsComponent::isSolid() {
    return solid;
}

bool PhysicsComponent::hasFriction() {
    return friction;
}

void PhysicsComponent::blacklistPhysics(uint8_t id) {
    physicsBlackList.push_back(id);
}


std::vector<uint8_t> PhysicsComponent::getPhysicsBlackList() {
    return physicsBlackList;
}