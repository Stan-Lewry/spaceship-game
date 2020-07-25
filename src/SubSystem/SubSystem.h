#pragma once

#include "../Utils/Debug.h"
#include <algorithm>

class SubSystem
{
public:
    SubSystem(double _updateInterval) : updateInterval(_updateInterval) {}
    virtual ~SubSystem() {}

    void setUpdateInterval(double i) {updateInterval = i;}
    void update(double dTime){
        timer += dTime;
        if (timer >= updateInterval) {
            timer = 0;
            doUpdate(dTime);
        }
    }
protected:
    virtual void doUpdate(double dTime) = 0;
private:
    double updateInterval;
    double timer = 0;
};