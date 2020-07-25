#pragma once

#include "../../Utils/Debug.h"
#include "../SubSystem.h"
#include "../../Component/WorldComponent.h"
#include "../../Component/RenderableComponent.h"
#include "TextureManager.h"

#include <list>

class IsometricRenderer : SubSystem {
public:
    IsometricRenderer(TextureManager* textureManager);
    IsometricRenderer(TextureManager* textureManager, float x, float y, float w, float h, float zoomLevel);
    virtual ~IsometricRenderer();

    void registerRenderable(WorldComponent* worldComp, RenderableComponent* rendComp);

protected:
    void doUpdate(double dTime) override;

private:

    void _renderObjects();
    void _renderBackground();
    void _renderTestBackground();
    void _renderTestReticule();

    std::list<std::pair<WorldComponent*, RenderableComponent*>> renderableComponents;

    TextureManager* textureManager;

    float cameraWorldX;
    float cameraWorldY;
    float zoomLevel;

    float viewportX;
    float viewportY;
    float viewportW;
    float viewportH;
};