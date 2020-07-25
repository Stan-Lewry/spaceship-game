#pragma once

#include "../../Utils/SDLUtils.h"
#include "../SubSystem.h"
#include "../../Component/WorldComponent.h"
#include "../../Component/InputComponent.h"

class InputSubSystem : public SubSystem{
public:
    InputSubSystem();
    virtual ~InputSubSystem();    
    void registerInputComponent(InputComponent* inputComp);
    void deRegisterInputComponent(InputComponent* inputComp);
protected:
    void doUpdate(double dTime) override;
private:
    void _pollInputs();

    std::list<InputComponent*> inputComponents;
    bool quitEvent;
    std::map<SDL_Keycode, std::pair<Button, bool>> inputStateMap = {
        {SDLK_UP, {upArrow, false}},
        {SDLK_DOWN, {downArrow, false}},
        {SDLK_LEFT, {leftArrow, false}},
        {SDLK_RIGHT, {rightArrow, false}},
        {SDLK_SPACE, {space, false}},
        {SDLK_F1, {f1, false}},
        {SDLK_F2, {f2, false}},
        {SDLK_F3, {f3, false}},
        {SDLK_F4, {f4, false}},
        {SDLK_F5, {f5, false}},
        {SDLK_F6, {f6, false}},
        {SDLK_F7, {f7, false}},
        {SDLK_F8, {f8, false}},
        {SDLK_F9, {f9, false}},
        {SDLK_F10, {f10, false}},
        {SDLK_F11, {f11, false}},
        {SDLK_F12, {f12, false}},
        {SDLK_RIGHTBRACKET, {rightSquareBracket, false}},
        {SDLK_LEFTBRACKET, {leftSquareBracket, false}},
        };
};