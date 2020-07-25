#include "PhysicsEntityTest.h"

PhysicsEntityTest::PhysicsEntityTest(WorldComponent* wc, PhysicsComponent* pc, InputComponent* ic)
    : Entity(1000 / 60) {
    worldComponent = wc;
    physicsComponent = pc;
    inputComponent = ic;
}

PhysicsEntityTest::~PhysicsEntityTest() {}

void PhysicsEntityTest::doUpdate() {
    vect<float> velocity = physicsComponent->getVelocity();
    float speed = 0.1f;

    if (inputComponent->getButtonState(upArrow)) {
        velocity.y = -speed;
    } if (inputComponent->getButtonState(downArrow)) {
        velocity.y = speed;
    } if (inputComponent->getButtonState(leftArrow)) {
        velocity.x = -speed;
    } if (inputComponent->getButtonState(rightArrow)) {
        velocity.x = speed;
    }

    physicsComponent->setVelocity(velocity);
}