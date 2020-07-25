#include "DebugRenderer.h"
#include <string>

DebugConsoleRenderer::DebugConsoleRenderer(float x, float y, float w, float h)
    : SubSystem(0)
    , viewportX(x)
    , viewportY(y)
    , viewportW(w)
    , viewportH(h) {
        consoleFont = TTF_OpenFont("assets/LiberationMono-Regular.ttf", 14);
    }

DebugConsoleRenderer::~DebugConsoleRenderer() {}

void DebugConsoleRenderer::doUpdate(double dTime) {
    drawConsole();
}

void DebugConsoleRenderer::drawConsole() {
    std::vector<std::string> debugStringList = globalDebugStringList;

    SDL_Rect bg = {viewportX, viewportY, viewportW, viewportH};

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 125);
    SDL_RenderFillRect(rend, &bg);

    SDL_Rect r ={0, viewportH, 0, 0};

    for (int i = debugStringList.size() - 1; i >=0; --i) {
        SDL_Surface* surf = TTF_RenderText_Blended(consoleFont, debugStringList.at(i).c_str(), white);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);
        r.w = surf->w;
        r.h = surf->h;
        r.y -= r.h;
        SDL_RenderCopy(rend, tex, nullptr, &r);
        SDL_FreeSurface(surf);
        SDL_DestroyTexture(tex);
    }
}

DebugRenderer::DebugRenderer(float x, float y, float w, float h, Camera* _cam, DebugInfo* _info)
    : SubSystem(0)
    , debugEntities()
    , debugFont()
    , info(_info)
    , cam(_cam)
    , viewportX(x)
    , viewportY(y)
    , viewportW(w)
    , viewportH(h) {
    debugFont = TTF_OpenFont("assets/LiberationMono-Regular.ttf", 18);
    debugFontSmall = TTF_OpenFont("assets/LiberationMono-Regular.ttf", 12);
    if (debugFont && debugFont) SDEBUG("Fonts loaded.");
}

DebugRenderer::~DebugRenderer() {

}

void DebugRenderer::registerDebugEntity(WorldComponent* worldCompo, PhysicsComponent* physicsCompo, color c) {
    debugEntities.push_back(std::make_pair(std::make_pair(worldCompo, physicsCompo), c));
}

void DebugRenderer::doUpdate(double dTime) {

    int centerX = viewportX + (viewportW / 2);
    int centerY = viewportY + (viewportH / 2);

    for (auto pair : debugEntities) {
        rect<float> box = pair.first.second->getBoundingBox();
        box.x += pair.first.first->getWorldX();
        box.y += pair.first.first->getWorldY();
        float XdistBetweenObjAndCam = box.x - cam->getPosition().x;
        float YdistBetweenObjAndCam = box.y - cam->getPosition().y;
        float XdistInScreenSpace = XdistBetweenObjAndCam * cam->getZoom();
        float YdistInScreenSpace = YdistBetweenObjAndCam * cam->getZoom();
        float objScreenX = centerX + XdistInScreenSpace;
        float objScreenY = centerY + YdistInScreenSpace;
        float objScreenW = box.w * cam->getZoom();
        float objScreenH = box.h * cam->getZoom();
        SDL_Rect dRect = {objScreenX, objScreenY, objScreenW, objScreenH};
        SDL_SetRenderDrawColor(rend, pair.second.r, pair.second.g, pair.second.b, pair.second.a);
        drawDebugBox(dRect);
        
        std::string xy = std::to_string(pair.first.first->getWorldX()).append(", ").append(std::to_string(pair.first.first->getWorldY()));
        drawDebugText(debugFontSmall, xy.c_str(), white, dRect.x, dRect.y);        
    }

    SDL_Rect t = drawDebugText(debugFont, "debug mode", white, viewportX + 5, viewportY + 5);
    t = drawDebugText(debugFont, std::string("fps: ").append(std::to_string(info->frameCount)).c_str(), white, viewportX + 5, t.y + t.h);
    drawDebugText(debugFont, std::string("camera: ").append(std::to_string(cam->getPosition().x)).append(", ").append(std::to_string(cam->getPosition().y)).append(" zoom: ").append(std::to_string(cam->getZoom())).c_str(), white, viewportX + 5, t.y + t.h);
}

SDL_Rect DebugRenderer::drawDebugText(TTF_Font* f, const char* m, SDL_Color c, int x, int y) {
    SDL_Surface* surf = TTF_RenderText_Blended(f, m, c);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);
    SDL_Rect mRect = {x, y, surf->w, surf->h};
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 125);
    SDL_RenderFillRect(rend, &mRect);
    SDL_RenderCopy(rend, tex, nullptr, &mRect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
    return mRect;
}

void DebugRenderer::drawDebugBox(SDL_Rect r) {
    int lw = 2;
    int bw = 6;

    SDL_Color c;

    SDL_Rect left = {r.x, r.y, lw, r.h};
    SDL_Rect right = {r.x + r.w - lw, r.y, lw, r.h};
    SDL_Rect top = {r.x, r.y, r.w, lw};
    SDL_Rect bottom = {r.x, r.y + r.h - lw, r.w, lw};
    SDL_Rect tlCorner = {r.x - (bw / 2), r.y - (bw / 2), bw, bw};
    SDL_Rect brCorner = {r.x + r.w - (bw / 2), r.y + r.h - (bw / 2), bw, bw};
    SDL_RenderFillRect(rend, &tlCorner);
    SDL_RenderFillRect(rend, &brCorner);
    SDL_RenderFillRect(rend, &left);
    SDL_RenderFillRect(rend, &right);
    SDL_RenderFillRect(rend, &top);
    SDL_RenderFillRect(rend, &bottom);
}