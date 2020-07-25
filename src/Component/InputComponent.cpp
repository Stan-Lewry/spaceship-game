#include "InputComponent.h"

InputComponent::InputComponent()
    : buttonStateMap()
{
    SDEBUG("Constructing an InputComponent");
}

InputComponent::InputComponent(std::list<Button> buttonList)
    :buttonStateMap()
{
    registerButton(buttonList);
}

InputComponent::~InputComponent()
{
    SDEBUG("Destructing an InputComponent");
}

void InputComponent::registerButton(Button newButton)
{
    buttonStateMap.insert(std::make_pair(newButton, false));
}

void InputComponent::registerButton(std::list<Button> buttons)
{
    for (auto b : buttons)
    {
        registerButton(b);
    }
}

void InputComponent::deRegisterButton(Button button)
{
    if (buttonStateMap.find(button) != buttonStateMap.end())
    {
        buttonStateMap.erase(button);
    }
}

bool InputComponent::getButtonState(Button b)
{
    return buttonStateMap.at(b);
}

void InputComponent::setButtonState(Button button, bool state)
{
    if (buttonStateMap.find(button) != buttonStateMap.end())
    {
        buttonStateMap.at(button) = state;
    }
}