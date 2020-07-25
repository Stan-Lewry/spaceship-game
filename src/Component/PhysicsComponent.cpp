#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(vect<vect<float>> _boundingBox, std::string _name, bool _solid)
    : boundingBox(_boundingBox)
    , velocity({0, 0})
    , name(_name)
    , currentCollisionList()
    , solid(_solid)
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