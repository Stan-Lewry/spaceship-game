#pragma once

#include "Component.h"

class WorldComponent : public Component {
public:
    WorldComponent();
    WorldComponent(float worldX, float worldY, float worldW, float worldH);
    WorldComponent(float worldX, float worldY, float worldW, float worldH, int worldZ);
    virtual ~WorldComponent();

    float getWorldX();
    float getWorldY();
    float getWorldW();
    float getWorldH();
    int getWorldZ() const;

    void setWorldX(float worldX);
    void setWorldY(float worldY);

private:
    float worldX;
    float worldY;
    float worldW;
    float worldH;
    const int worldZ;
};