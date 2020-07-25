#include "Renderer2D.h"

Renderer2D::Renderer2D(TextureManager* _textureManager)
    : Renderer2D(_textureManager, 0,0, screenW, screenH, new Camera()) {
}

Renderer2D::Renderer2D(TextureManager* _textureManager, float x, float y, float w, float h, Camera* _cam)
    : SubSystem(0)
    , renderableComponents()
    , textureManager(_textureManager)
    , cam(_cam)
    , viewportX(x)
    , viewportY(y)
    , viewportW(w)
    , viewportH(h) {
    SDEBUG("Constructing Renderer2D");
}

Renderer2D::~Renderer2D() {
    SDEBUG("Destructing Renderer2D");
}

void Renderer2D::doUpdate(double dTime) {
    _renderTestBackground();
    _renderObjects();
}

void Renderer2D::registerRenderable(WorldComponent* worldComp, RenderableComponent* rendComp) {
    auto it = std::find_if(renderableComponents.begin(), renderableComponents.end(), [worldComp](const std::pair<WorldComponent*,RenderableComponent*>& pair){
        return pair.first->getWorldZ() > worldComp->getWorldZ();
    });
    renderableComponents.insert(it, std::make_pair(worldComp, rendComp));
}

void Renderer2D::deRegisterRenderable(WorldComponent* worldComp, RenderableComponent* rendComp) {
    auto it = std::find(renderableComponents.begin(), renderableComponents.end(), std::make_pair(worldComp, rendComp));
    if (it != renderableComponents.end()) {
        renderableComponents.erase(it);
    }
}

void Renderer2D::deRegisterRenderable(RenderableComponent* rendComp) {
    auto it = std::find_if(renderableComponents.begin(), renderableComponents.end(), [rendComp](const std::pair<WorldComponent*,RenderableComponent*>& pair){
        return pair.second == rendComp;
    });
    if (it != renderableComponents.end()) {
        renderableComponents.erase(it);
    }
}

void Renderer2D::_renderObjects() {
    // find the center of the screen
    int centerX = viewportX + (viewportW / 2);
    int centerY = viewportY + (viewportH / 2);

    for (auto pair : renderableComponents) {
        if (pair.second->getVisible()) {
            // find the distance between the object and the cameras focal point in world space
            float XdistBetweenObjAndCam = pair.first->getWorldX() - cam->getPosition().x;
            float YdistBetweenObjAndCam = pair.first->getWorldY() - cam->getPosition().y;

            // use the zoom level as the ratio of meters (world) to pixels (screen) to 
            // translate this distance to screen space.
            float XdistInScreenSpace = XdistBetweenObjAndCam * cam->getZoom();
            float YdistInScreenSpace = YdistBetweenObjAndCam * cam->getZoom();

            // so the position of the object is the center of the screen + the
            // previously calculated distance in pixels
            float objScreenX = centerX + XdistInScreenSpace;
            float objScreenY = centerY + YdistInScreenSpace;

            // scale the object by zoom level (meters:pixel ratio)
            float objScreenW = pair.first->getWorldW() * cam->getZoom();
            float objScreenH = pair.first->getWorldH() * cam->getZoom();

            SDL_Rect dRect = {objScreenX, objScreenY, objScreenW, objScreenH};

            Texture* texture = textureManager->getTexture(pair.second->getTextureId());

            if (texture) {
                SDL_RenderCopy(rend, texture->spriteSheet, &texture->sourceRect, &dRect);
            } else {
                SERROR("Failed to find resource %s", pair.second->getTextureId().c_str());
                // draw a big ugly green rectangle
                SDL_SetRenderDrawColor(rend, 0, 255, 0, 1);
                SDL_RenderFillRect(rend, &dRect);
            }
        }
    }
}

void Renderer2D::_renderBackground() {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderFillRect(rend, NULL);
}

void Renderer2D::_renderTestBackground() {
    SDL_Rect outsideRect = {viewportX, viewportY, viewportW, viewportH};
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderFillRect(rend, &outsideRect);

    SDL_Rect insideRect = {viewportX + 5, viewportY + 5, viewportW - 10, viewportH - 10};
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderFillRect(rend, &insideRect);

    // render a small point at the center of the screen

    int centerX = viewportX + (viewportW / 2);
    int centerY = viewportY + (viewportH / 2);

    SDL_Rect middleBox = {centerX - 3, centerY - 3, 6, 6};
    SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
    SDL_RenderFillRect(rend, &middleBox);
}
