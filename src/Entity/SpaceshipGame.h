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

class Bullet : public Entity {
public:
    Bullet(float x, float y);
    virtual ~Bullet();
    bool isDead() const;
    void setDead(bool d);
    void setPos(vect<float> p);
protected:
    void doUpdate() override;
private:
    WorldComponent* world;
    RenderableComponent* rend;
    PhysicsComponent* phys;
    bool dead;
};
	

class PlayerShip : public Entity {
public:
    PlayerShip();
    virtual ~PlayerShip();
protected:
    void doUpdate() override;
private:
    void createBullet();

    WorldComponent* world;
    RenderableComponent* rend;
    InputComponent* input;
    PhysicsComponent* phys;
    std::vector<Bullet*> bulletList;

    std::vector<Bullet*> bulletPool;
};

class Asteroid : public Entity {
public:
    Asteroid();
    virtual ~Asteroid();
protected:
    void doUpdate() override;
private:
    WorldComponent* world;
    RenderableComponent* rend;
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
