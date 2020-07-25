#pragma once

#include "Entity.h"

#include "../Component/InputComponent.h"
#include "../Component/WorldComponent.h"

class SimpleInputEntityTest : public Entity {
public:
    SimpleInputEntityTest(InputComponent* inputComponent, WorldComponent* worldComponent);
    virtual ~SimpleInputEntityTest();    

protected:
    void doUpdate() override;

private:
    InputComponent* inputComponent;
    WorldComponent* worldComponent;
};