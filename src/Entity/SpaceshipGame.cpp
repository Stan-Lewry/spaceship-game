#include "SpaceshipGame.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static constexpr float startX = -32.0f;

static constexpr uint8_t shipPhysId = 1;
static constexpr uint8_t bulletPhysId = 2;
static constexpr uint8_t asteroidPhysId = 3;

Background::Background() {
    panel1 = GameEngine::createWorldComponent(startX, -24, 64, 48, 0);
    panel1Rend = GameEngine::createRenderableComponent("stars", true, panel1);

    panel2 = GameEngine::createWorldComponent(panel1->getWorldX() + 64, panel1->getWorldY(), 64, 48, 0);
    panel2Rend = GameEngine::createRenderableComponent("stars", true, panel2);

    GameEngine::registerEntity(this);
}

Background::~Background() {
    GameEngine::deleteRenderableComponent(panel1Rend);
    GameEngine::deleteRenderableComponent(panel2Rend);
    GameEngine::deleteWorldComponent(panel1);
    GameEngine::deleteWorldComponent(panel2);
    GameEngine::deRegisterEntity(this);
}

void Background::doUpdate() {
    if (panel1->getWorldX() < startX - panel1->getWorldW()) {
        panel1->setWorldX(panel2->getWorldX() + panel2->getWorldW());
    }
    
    if (panel2->getWorldX() < startX - panel2->getWorldW()) {
        panel2->setWorldX(panel1->getWorldX() + panel1->getWorldW());
    }

    panel1->setWorldX(panel1->getWorldX() - 0.05f);
    panel2->setWorldX(panel2->getWorldX() - 0.05f);
}

Bullet::Bullet(float x, float y) {
    world = GameEngine::createWorldComponent(x, y, 1.5, 0.5, 1);
    rend = GameEngine::createRenderableComponent("bullet", true, world);
    phys = GameEngine::createPhysicsComponent({{0, 0}, {3, 1}}, bulletPhysId, false, false, world);
    phys->blacklistPhysics(shipPhysId);
    phys->blacklistPhysics(bulletPhysId);
    phys->blacklistPhysics(asteroidPhysId);
    phys->setVelocity({1.5, 0});
    GameEngine::registerEntity(this);
    dead = false;
}

Bullet::~Bullet() {
    GameEngine::deleteRenderableComponent(rend);
    GameEngine::deletePhysicsComponent(phys);
    GameEngine::deleteWorldComponent(world);
    GameEngine::deRegisterEntity(this);
}

void Bullet::doUpdate(){
    if (!dead) {
        if (world->getWorldX() > 32.0f) {
            dead = true;
            world->setWorldX(-100);
            world->setWorldY(-100);
        } 
    }
}

bool Bullet::isDead() const {
    return dead;
}

void Bullet::setDead(bool d){
    dead = d;
}

void Bullet::setPos(vect<float> pos) {
    world->setWorldX(pos.x);
    world->setWorldY(pos.y);
}

static constexpr int bulletPoolSize = 20;
static int bulletIndex = 0;

PlayerShip::PlayerShip()
    : world(GameEngine::createWorldComponent(-20, -10, 10, 10, 1))
    , rend(GameEngine::createRenderableComponent("ship_normal", true, world))
    , phys(GameEngine::createPhysicsComponent({{0, 0}, {10, 10}}, shipPhysId, true, true, world))
    , input(GameEngine::createInputComponent({upArrow, downArrow, leftArrow, rightArrow, space}))
    , bulletList()
    , bulletPool() {
    
    phys->blacklistPhysics(bulletPhysId);
    phys->blacklistPhysics(asteroidPhysId);

    GameEngine::registerEntity(this);

    for (int i = 0; i < bulletPoolSize; ++i) {
        Bullet* b = new Bullet(-100, -100);
        b->setDead(true);
        bulletPool.push_back(b);
    }
}

PlayerShip::~PlayerShip() {
    GameEngine::deleteInputComponent(input);
    GameEngine::deleteRenderableComponent(rend);
    GameEngine::deletePhysicsComponent(phys);
    GameEngine::deleteWorldComponent(world);
    GameEngine::deRegisterEntity(this);
}

void PlayerShip::doUpdate() {
    static constexpr double bulletUpdateInterval = 60;
    static double bulletUpdateTimer = 0;
    static bool canShoot = false;
    
    bulletUpdateTimer += delta;
    if (bulletUpdateTimer >= bulletUpdateInterval) {
        bulletUpdateTimer = 0;
        canShoot = true;
    }

    vect<float> vel = {0, 0};

    std::string spriteId = "ship_normal";
    if (input->getButtonState(upArrow)) {
        vel.y = -1.0f;
        spriteId = "ship_up";
    }
    if (input->getButtonState(downArrow)) {
        vel.y = 1.0f;
        spriteId = "ship_down";
    }
    if (input->getButtonState(leftArrow)) {
        vel.x = -1.0f;
    }
    if (input->getButtonState(rightArrow)) {
        vel.x = 1.0f;
    }
    if (input->getButtonState(space) && canShoot) {
        canShoot = false;
        createBullet();
    }

    phys->setVelocity(vel);
    rend->setTextureId(spriteId);
}

void PlayerShip::createBullet() {
    Bullet* b = bulletPool.at(bulletIndex);
    b->setPos({world->getWorldX() + world->getWorldW(), world->getWorldY() + (world->getWorldH() / 2)});
    b->setDead(false);
    (bulletIndex == bulletPoolSize - 1) ? bulletIndex = 0 : ++bulletIndex;
}

static const int startPosNo = 8;
static const int speedNo = 4;
static const int spritesNo = 3;
static const float startYPositions[startPosNo] = {-20.0f, -15.0f, -10.0f, -5.0f, 0.0f, 5.0f, 10.0f, 15.0f};
static const float startXPositions[startPosNo] = {32.0f, 32.0f, 42.0f, 42.0f, 52.0f, 52.0f, 62.0f, 62.0f};
static const float speeds[speedNo] = {-0.5f, -0.7f, -0.8f, -0.2f};
static const std::string spriteIds[spritesNo] = {"asteroid_1", "asteroid_2", "asteroid_3"};

Asteroid::Asteroid() {
    int randomI = rand() % startPosNo + 1;
    float startY = startYPositions[randomI - 1];
    randomI = rand() % startPosNo + 1;
    float startX = startXPositions[randomI - 1];
    randomI = rand() % speedNo + 1;
    float speed = speeds[randomI - 1];
    randomI = rand() % spritesNo + 1;
    std::string spriteId = spriteIds[randomI - 1];

    world = GameEngine::createWorldComponent(startX, startY, 10, 10, 2);
    rend = GameEngine::createRenderableComponent(spriteId, true, world);
    phys = GameEngine::createPhysicsComponent({{0, 0}, {10, 10}}, asteroidPhysId, false, false, world);
    phys->setVelocity({speed, 0});
    phys->blacklistPhysics(asteroidPhysId);
    phys->blacklistPhysics(bulletPhysId);
    phys->blacklistPhysics(shipPhysId);

    GameEngine::registerEntity(this);
}
    
Asteroid::~Asteroid() {
    GameEngine::deleteRenderableComponent(rend);
    GameEngine::deletePhysicsComponent(phys);
    GameEngine::deleteWorldComponent(world);
    GameEngine::deRegisterEntity(this);
}

void Asteroid::doUpdate() {
    if (world->getWorldX() < -42) {
        int randomI = rand() % startPosNo + 1;
        float startY = startYPositions[randomI - 1];
        randomI = rand() % startPosNo + 1;
        float startX = startXPositions[randomI - 1];
        randomI = rand() % speedNo + 1;
        float speed = speeds[randomI - 1];
        randomI = rand() % spritesNo + 1;
        std::string spriteId = spriteIds[randomI - 1];

        world->setWorldX(startX);
        world->setWorldY(startY);
        phys->setVelocity({speed, 0});
        rend->setTextureId(spriteId);
    }
}

static const int asteroidPoolCount = 4;

SpaceshipGame::SpaceshipGame() {
    background = new Background();
    playerShip = new PlayerShip();
    input = GameEngine::createInputComponent({space});
    GameEngine::registerEntity(this);

    srand(time(NULL));

    for (int i = 0; i < asteroidPoolCount; ++i) {
        Asteroid* a = new Asteroid();
        asteroidPool.push_back(a);
    }
}

SpaceshipGame::~SpaceshipGame() {
    if (background != nullptr) delete background;
    if (playerShip != nullptr) delete playerShip;
    GameEngine::deRegisterEntity(this);
}

void SpaceshipGame::doUpdate() {
}