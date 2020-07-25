#include "SimpleInputEntityTest.h"

SimpleInputEntityTest::SimpleInputEntityTest(InputComponent* _inputComponent, WorldComponent* _worldComponent)
    : Entity(1000 / 60)
    , inputComponent(_inputComponent)
    , worldComponent(_worldComponent) {
    SDEBUG("Constructing simple input entity test with an inputComponet");
}

SimpleInputEntityTest::~SimpleInputEntityTest() {
    SDEBUG("Destructing simple inout entity test");
}

void SimpleInputEntityTest::doUpdate() {
    if (inputComponent->getButtonState(upArrow)) {
        worldComponent->setWorldY(worldComponent->getWorldY() - 10);
    } if (inputComponent->getButtonState(downArrow)) {
        worldComponent->setWorldY(worldComponent->getWorldY() + 10);
    } if (inputComponent->getButtonState(leftArrow)) {
        worldComponent->setWorldX(worldComponent->getWorldX() - 10);
    } if (inputComponent->getButtonState(rightArrow)) {
        worldComponent->setWorldX(worldComponent->getWorldX() + 10);
    }
}