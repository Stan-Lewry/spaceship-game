#include "RenderableComponent.h"

RenderableComponent::RenderableComponent(std::string _textureId)
    : RenderableComponent(_textureId, true) {}

RenderableComponent::RenderableComponent(std::string _textureId, bool _visible)
    : textureId(_textureId)
    , visible(_visible) {}

RenderableComponent::~RenderableComponent() {
    SDEBUG("Destructing RenderableComponent");
}

std::string RenderableComponent::getTextureId() {
    return textureId;
}

void RenderableComponent::setTextureId(std::string tid) {
    textureId = tid;
}

bool RenderableComponent::getVisible() {
    return visible;
}

void RenderableComponent::setVisible(bool _visible) {
    visible = _visible;
}
