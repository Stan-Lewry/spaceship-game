#pragma once

#include "../../Utils/SDLUtils.h"
#include "../SubSystem.h"
#include "../../Component/WorldComponent.h"
#include "../../Component/PhysicsComponent.h"
#include "../../Entity/Camera.h"

#include <list>

struct DebugInfo {
    DebugInfo() : frameCount(0) {}
    int frameCount;
};

class DebugConsoleRenderer : public SubSystem {
public:
    DebugConsoleRenderer(float x, float y, float w, float h);
    virtual ~DebugConsoleRenderer();

protected:
    void doUpdate(double dTime) override;
private:
    void drawConsole();
    TTF_Font* consoleFont;

    float viewportX;
    float viewportY;
    float viewportW;
    float viewportH;
};

class DebugRenderer : public SubSystem {
public:
    DebugRenderer(float x, float y, float w, float h, Camera* cam, DebugInfo* info);
    virtual ~DebugRenderer();

    void registerDebugEntity(WorldComponent* worldCompo, PhysicsComponent* physicsCompo, color col);
    void deRegisterDebugEntity(PhysicsComponent* physicsCompo);
protected:
    void doUpdate(double dTime) override;

private:
    void drawDebugBox(SDL_Rect r);
    SDL_Rect drawDebugText(TTF_Font* f, const char* m, SDL_Color c, int x, int y);

    std::list<std::pair<std::pair<WorldComponent*, PhysicsComponent*>, color>> debugComponents;

    TTF_Font* debugFont;
    TTF_Font* debugFontSmall;
    DebugInfo* info;
    Camera* cam;

    float viewportX;
    float viewportY;
    float viewportW;
    float viewportH;
};