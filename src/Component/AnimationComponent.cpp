#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(std::vector<std::string> _frames, double _interval)
    : AnimationComponent(_frames, _interval, false) {

}

AnimationComponent::AnimationComponent(std::vector<std::string> _frames, double _interval, bool _loop)
    : AnimationComponent(_frames, _interval, _loop, false) {

}

AnimationComponent::AnimationComponent(std::vector<std::string> _frames, double _interval, bool _loop, bool _play)
    : frames(_frames)
    , interval(_interval)
    , clock(0)
    , loop(_loop)
    , play(_play)
    , currentFrameIndex(0)  {
}

AnimationComponent::~AnimationComponent() {}

std::string AnimationComponent::getCurrentFrame() {
    return frames.at(currentFrameIndex);
}

double AnimationComponent::getInterval() {
    return interval;
}

double AnimationComponent::getClock() {
    return clock;
}

void AnimationComponent::tickClock(double delta) {
    clock += delta;
}

void AnimationComponent::resetClock() {
    clock = 0;
}

bool AnimationComponent::getLoop() {
    return loop;
}

bool AnimationComponent::getPlay() {
    return play;
}

void AnimationComponent::setPlay(bool p) {
    play = p;
}

int AnimationComponent::getCurrentFrameIndex() {
    return currentFrameIndex;
}

void AnimationComponent::incrementFrameIndex() {
    currentFrameIndex += 1;
}

void AnimationComponent::setCurrentFrameIndex(int i) {
    currentFrameIndex = i;
}

int AnimationComponent::getMaxFrame() {
    return (int)frames.size() - 1;
}