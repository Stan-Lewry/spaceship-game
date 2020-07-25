#include "IsometricRenderer.h"

IsometricRenderer::IsometricRenderer(TextureManager* _textureManager)
    : IsometricRenderer(_textureManager, 0,0, screenW, screenH, 40.0f) {}

IsometricRenderer::IsometricRenderer(TextureManager* _textureManager, float x, float y, float w, float h, float _zoomLevel)
    : SubSystem(0)
    , renderableComponents()
    , textureManager(_textureManager)
    , cameraWorldX(1.0f)
    , cameraWorldY(1.0f)
    , zoomLevel(_zoomLevel)
    , viewportX(x)
    , viewportY(y)
    , viewportW(w)
    , viewportH(h) {
    SDEBUG("Constructing IsometricRenderer");
}

IsometricRenderer::~IsometricRenderer() {}

void IsometricRenderer::doUpdate(double dTime) {
    _renderTestBackground();
    _renderObjects();
    _renderTestReticule();
}

void IsometricRenderer::registerRenderable(WorldComponent* worldComp, RenderableComponent* rendComp) {
    renderableComponents.push_back(std::make_pair(worldComp, rendComp));
}

void IsometricRenderer::_renderObjects() {
    // screen x = (map x - map y) * (tile w / 2)
    // screen y = (map x + map y) * (tile h / 2)
    
    // find the center of the screen
    int centerX = viewportX + (viewportW / 2);
    int centerY = viewportY + (viewportH / 2);

    for (auto pair : renderableComponents) {
        if (pair.second->getVisible()) {
            float worldX = pair.first->getWorldX();
            float worldY = pair.first->getWorldY();
            float worldW = pair.first->getWorldW();
            float worldH = pair.first->getWorldH();

            float objScreenH = worldH * zoomLevel;
            float objScreenW = worldW * zoomLevel;
            float objScreenX;
            float objScreenY;

            // the objects world coords relative to the camera
            float XFromCam = (worldX - cameraWorldX);
            float YFromCam = (worldY - cameraWorldY);

            objScreenX = (XFromCam - YFromCam) * (zoomLevel / 2);
            objScreenY = (XFromCam + YFromCam) * (zoomLevel / 4);

            objScreenX += centerX;
            objScreenY += centerY;

            SDL_Rect dRect = {objScreenX, objScreenY, objScreenW, objScreenH};

            Texture* texture = textureManager->getTexture(pair.second->getTextureId());

            SDL_RenderCopy(rend, texture->spriteSheet, &texture->sourceRect, &dRect);
        }
    }
}

void IsometricRenderer::_renderBackground() {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 1);
    SDL_RenderFillRect(rend, NULL);
}

void IsometricRenderer::_renderTestBackground() {
    SDL_Rect outsideRect = {viewportX, viewportY, viewportW, viewportH};
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 1);
    SDL_RenderFillRect(rend, &outsideRect);

    SDL_Rect insideRect = {viewportX + 5, viewportY + 5, viewportW - 10, viewportH - 10};
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 1);
    SDL_RenderFillRect(rend, &insideRect);
}

void IsometricRenderer::_renderTestReticule() {
    // render a small point at the center of the screen

    int centerX = viewportX + (viewportW / 2);
    int centerY = viewportY + (viewportH / 2);

    SDL_Rect middleBox = {centerX - 3, centerY - 3, 6, 6};
    SDL_SetRenderDrawColor(rend, 0, 0, 255, 1);
    SDL_RenderFillRect(rend, &middleBox);
}