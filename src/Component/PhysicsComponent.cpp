#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(vect<vect<float>> _boundingBox, std::string _name, bool _solid)
    : PhysicsComponent(_boundingBox, _name, _solid, true)
{}

PhysicsComponent::PhysicsComponent(vect<vect<float>> _boundingBox, std::string _name, bool _solid, bool _friction)
    : boundingBox(_boundingBox)
    , velocity({0, 0})
    , name(_name)
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

void PhysicsComponent::setPhysicsBlackList(std::vector<std::string> _physicsBlackList) {
    physicsBlackList = _physicsBlackList;
}


std::vector<std::string> PhysicsComponent::getPhysicsBlackList() {
    return physicsBlackList;
}