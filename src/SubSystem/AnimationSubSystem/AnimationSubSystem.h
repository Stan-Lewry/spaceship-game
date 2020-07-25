#pragma once

#include "../SubSystem.h"
#include "../../Component/AnimationComponent.h"
#include "../../Component/RenderableComponent.h"

class AnimationSubSystem : public SubSystem {
public:
    AnimationSubSystem();
    virtual ~AnimationSubSystem();
    void registerAnimationEntity(AnimationComponent* animCompo, RenderableComponent* rendCompo);

protected:
    void doUpdate(double dTime) override;
private:
    std::list<std::pair<AnimationComponent*, RenderableComponent*>> animList;
};
