#pragma once

#include "../Utils/Types.h"
#include "../Utils/Debug.h"
#include "Entity.h"
#include "../Component/WorldComponent.h"

class Camera : public Entity {
public:
    Camera();
    Camera(vect<float> position, float zoom);
    virtual ~Camera();

    vect<float> getPosition();
    void setPosition(vect<float> position);
    float getZoom();
    void setZoom(float zoom);
    void setFollowing(WorldComponent* wc);
    void stopFollowing();

protected:
    void doUpdate() override;
private:
    vect<float> position;
    float zoom;
    WorldComponent* following;
    bool isFollowing;
};