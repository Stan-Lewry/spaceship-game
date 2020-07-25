#pragma once

#include "Entity.h"
#include "../GameEngine.h"

class Background : public Entity {
public:
    Background();
    virtual ~Background();
protected:
    void doUpdate() override;
private:
    WorldComponent* panel1;
    WorldComponent* panel2;
    RenderableComponent* panel1Rend;
    RenderableComponent* panel2Rend;
};

class PlayerShip : public Entity {
public:
    PlayerShip();
    virtual ~PlayerShip();
protected:
    void doUpdate() override;
private:
    WorldComponent* world;
    RenderableComponent* rend;
    InputComponent* input;
    PhysicsComponent* phys;
};

class SpaceshipGame : public Entity {
public:
    SpaceshipGame();
    virtual ~SpaceshipGame();
protected:
    void doUpdate() override;
private:
    InputComponent* input;
    Background* background;
    PlayerShip* playerShip;
};