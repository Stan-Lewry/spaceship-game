#include "WorldComponent.h"

WorldComponent::WorldComponent()
    : WorldComponent(0.0f, 0.0f, 0.0f, 0.0f, 0) {
}

WorldComponent::WorldComponent(float worldX, float worldY, float worldW, float worldH)
    : WorldComponent(worldX, worldY, worldW, worldH, 0) {}

WorldComponent::WorldComponent(float _worldX, float _worldY, float _worldW, float _worldH, int _worldZ)
    : worldX(_worldX)
    , worldY(_worldY)
    , worldW(_worldW)
    , worldH(_worldH)
    , worldZ(_worldZ) {}

WorldComponent::~WorldComponent() {
    SDEBUG("Destructing WorldComponent");
}

float WorldComponent::getWorldX() {
    return worldX;
}

float WorldComponent::getWorldY() {
    return worldY;
}

float WorldComponent::getWorldW() {
    return worldW;
}

float WorldComponent::getWorldH() {
    return worldH;
}

int WorldComponent::getWorldZ() const {
    return worldZ;
}

void WorldComponent::setWorldX(float _worldX) {
    worldX = _worldX;
}

void WorldComponent::setWorldY(float _worldY) {
    worldY = _worldY;
}