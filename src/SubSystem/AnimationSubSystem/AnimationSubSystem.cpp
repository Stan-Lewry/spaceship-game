#include "AnimationSubSystem.h"

AnimationSubSystem::AnimationSubSystem()
    : SubSystem(0) {}

AnimationSubSystem::~AnimationSubSystem() {}

void AnimationSubSystem::registerAnimationEntity(AnimationComponent* animCompo, RenderableComponent* rendCompo) {
    animList.push_back({animCompo, rendCompo});
}

void AnimationSubSystem::doUpdate(double dTime) {
    for (auto pair : animList) {
        if (pair.first->getPlay()){
            AnimationComponent* a = pair.first;
            RenderableComponent* r = pair.second;

            a->tickClock(dTime);
            if (a->getClock() >= a->getInterval()) {
                a->resetClock();
                r->setTextureId(a->getCurrentFrame());
                a->incrementFrameIndex();

                if (a->getCurrentFrameIndex() > a->getMaxFrame()) {
                    if (a->getLoop()) {
                        a->setCurrentFrameIndex(0);
                    } else a->setPlay(false);
                }
            }
        }
    }
}

