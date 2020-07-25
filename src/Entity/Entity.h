#pragma once

#include "../Utils/Debug.h"

class Entity {
public:
    Entity() : Entity(0) {}
    Entity(double _updateInterval) : updateInterval(_updateInterval) {}
    virtual ~Entity() {}

    void setUpdateInterval(double i) {updateInterval = i;}
    void update(double dTime){
        timer += dTime;
        if (timer >= updateInterval) {
            timer = 0;
            doUpdate();
        }
    }
protected:
    virtual void doUpdate() = 0;
private:
    double updateInterval;
    double timer = 0;
};