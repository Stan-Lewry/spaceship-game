#include "SpaceshipGame.h"

static float startX = -32.0f;

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

PlayerShip::PlayerShip() {
    world = GameEngine::createWorldComponent(-20, -10, 10, 10, 1);
    rend = GameEngine::createRenderableComponent("ship_normal", true, world);
    phys = GameEngine::createPhysicsComponent({{0, 0}, {10, 10}}, "player_ship", true, world);
    input = GameEngine::createInputComponent({upArrow, downArrow, leftArrow, rightArrow, space});

    GameEngine::registerEntity(this);
}

PlayerShip::~PlayerShip() {
    GameEngine::deleteInputComponent(input);
    GameEngine::deleteRenderableComponent(rend);
    GameEngine::deletePhysicsComponent(phys);
    GameEngine::deleteWorldComponent(world);
    GameEngine::deRegisterEntity(this);
}

void PlayerShip::doUpdate() {
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

    phys->setVelocity(vel);
    rend->setTextureId(spriteId);
}

SpaceshipGame::SpaceshipGame() {
    background = new Background();
    playerShip = new PlayerShip();
    input = GameEngine::createInputComponent({space});
    GameEngine::registerEntity(this);
}

SpaceshipGame::~SpaceshipGame() {
    if (background != nullptr) delete background;
    if (playerShip != nullptr) delete playerShip;
    GameEngine::deRegisterEntity(this);
}

void SpaceshipGame::doUpdate() {
    if (input->getButtonState(space) && playerShip != nullptr) {
        delete playerShip;
        playerShip = nullptr;
    }
}
