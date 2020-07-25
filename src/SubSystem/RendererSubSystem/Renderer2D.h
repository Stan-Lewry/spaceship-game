#pragma once

#include "../../Utils/Types.h"
#include "../SubSystem.h"
#include "../../Component/WorldComponent.h"
#include "../../Component/RenderableComponent.h"
#include "TextureManager.h"
#include "../../Entity/Camera.h"

#include <list>

class Renderer2D : public SubSystem {
public:
    Renderer2D(TextureManager* textureManager);
    Renderer2D(TextureManager* textureManager, float x, float y, float w, float h, Camera* cam);
    virtual ~Renderer2D();

    void registerRenderable(WorldComponent* worldComp, RenderableComponent* rendComp);
    void deRegisterRenderable(WorldComponent* worldComp, RenderableComponent* rendComp);
    void deRegisterRenderable(RenderableComponent* rendComp);

protected:
    void doUpdate(double dTime) override;

private:
    void _renderObjects();
    void _renderBackground();
    void _renderTestBackground();

    std::list<std::pair<WorldComponent*, RenderableComponent*>> renderableComponents;

    TextureManager* textureManager;
    Camera* cam;
    float viewportX;
    float viewportY;
    float viewportW;
    float viewportH;
};