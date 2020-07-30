#pragma once

#include "Utils/Debug.h"
#include "SubSystem/RendererSubSystem/Renderer2D.h"
#include "SubSystem/RendererSubSystem/DebugRenderer.h"
#include "Entity/Camera.h"
#include "SubSystem/InputSubSystem/InputSubSystem.h"
#include "SubSystem/PhysicsSubSystem/PhysicsSubSystem.h"
#include "SubSystem/AnimationSubSystem/AnimationSubSystem.h"

#include "Entity/PhysicsEntityTest.h"
#include "Entity/SimpleWorldEntity.h"

class GameEngine
{
private:
    static GameEngine* instance;
public:
    void run();

    static GameEngine* getInstance() {
        if (!instance){
            instance = new GameEngine();
        }

        return instance;
    }

    static WorldComponent* createWorldComponent(float x, float y, float w, float h, float z);
    static RenderableComponent* createRenderableComponent(std::string textureId, bool visible, WorldComponent* world);
    static InputComponent* createInputComponent(std::list<Button> buttons);
    static PhysicsComponent* createPhysicsComponent(vect<vect<float>> boundingBox, std::string name, bool solid, bool friction, WorldComponent* world);
    static AnimationComponent* createAnimationComponent(std::vector<std::string> frames, double interval, bool loop, bool play, RenderableComponent* renderable);
    static void deleteRenderableComponent(RenderableComponent* rend);
    static void deleteInputComponent(InputComponent* input);
    static void deletePhysicsComponent(PhysicsComponent* physics);
    static void deleteWorldComponent(WorldComponent* world);

    static void registerEntity(Entity* entity);
    static void deRegisterEntity(Entity* entity);
private:
    GameEngine();
    virtual ~GameEngine();

    void initEntities();

    Camera* cam;

    InputSubSystem* input;
    PhysicsSubSystem* phys;
    Renderer2D* renderer;
    
    DebugInfo* debugInfo;
    DebugRenderer* debugRenderer;    
    DebugConsoleRenderer* debugConsoleRenderer;

    AnimationSubSystem* anim;

    std::vector<Entity*> entityList;
};

