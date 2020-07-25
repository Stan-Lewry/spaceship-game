#pragma once

#include "Component.h"
#include "../Utils/Types.h"

#include <map>

class InputComponent : public Component
{
public:
    InputComponent();
    InputComponent(std::list<Button> buttons);
    virtual ~InputComponent();

    void registerButton(Button newButton);
    void registerButton(std::list<Button> inputs);

    void deRegisterButton(Button input);
    
    bool getButtonState(Button input);

    void setButtonState(Button button, bool state);
private:
    typedef std::map<Button, bool> ButtonStateMap;
    ButtonStateMap buttonStateMap;
};