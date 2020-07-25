#include "InputSubSystem.h"

InputSubSystem::InputSubSystem()
    : SubSystem(0)
    , inputComponents()
    , quitEvent(false) {
    SDEBUG("Constructing InputSubSystem");
}

InputSubSystem::~InputSubSystem() {
    SDEBUG("Destructing InputSubSytem");
}

void InputSubSystem::doUpdate(double dTime) {
    _pollInputs();

    for (auto comp : inputComponents) {
        comp->setButtonState(quit, quitEvent);
    }

    for (auto b : inputStateMap) {
        for (auto comp : inputComponents) {
            comp->setButtonState(b.second.first, b.second.second);
        }
    }
}

void InputSubSystem::registerInputComponent(InputComponent* inputComp) {
    inputComponents.push_back(inputComp);
}

void InputSubSystem::deRegisterInputComponent(InputComponent* inputComp) {
    auto it = std::find(inputComponents.begin(), inputComponents.end(), inputComp);
    if (it != inputComponents.end()) inputComponents.erase(it);
}

void InputSubSystem::_pollInputs() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quitEvent = true;
                break;
            case SDL_KEYDOWN:
                inputStateMap[event.key.keysym.sym].second = true;
                break;
            case SDL_KEYUP:
                inputStateMap[event.key.keysym.sym].second = false;
                break;
        }
    }
}