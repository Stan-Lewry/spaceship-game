#pragma once

#include "Component.h"
#include "../Utils/SDLUtils.h"

#include <string>

class RenderableComponent : public Component
{
public:
    RenderableComponent(std::string textureId);
    RenderableComponent(std::string textureId, bool visible);
    virtual ~RenderableComponent();

    std::string getTextureId();
    void setTextureId(std::string tid);

    bool getVisible();
    void setVisible(bool visible);

private:
    std::string textureId;
    bool visible;
};