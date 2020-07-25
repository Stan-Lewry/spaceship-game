#pragma once

#include "Component.h"
#include "../Utils/Types.h"
#include <vector>

class AnimationComponent : public Component {
public:
    AnimationComponent(std::vector<std::string> frames, double interval);
    AnimationComponent(std::vector<std::string> frames, double interval, bool loop);
    AnimationComponent(std::vector<std::string> frames, double interval, bool loop, bool play);
    virtual ~AnimationComponent();

    std::string getCurrentFrame();
    double getInterval();
    double getClock();
    void tickClock(double delta);
    void resetClock();
    bool getLoop();
    bool getPlay();
    void setPlay(bool p);
    int getCurrentFrameIndex();
    void incrementFrameIndex();
    void setCurrentFrameIndex(int i);
    int getMaxFrame();
private:
    std::vector<std::string> frames;
    double interval;
    double clock;
    bool loop;
    bool play;
    int currentFrameIndex;
};
