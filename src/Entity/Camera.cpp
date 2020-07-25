#include "Camera.h"

Camera::Camera()
    : Camera({0, 0}, 1.0f) {}

Camera::Camera(vect<float> _position, float _zoom)
    : Entity()
    , position(_position)
    , zoom(_zoom)
    , following(nullptr)
    , isFollowing(false) {}

Camera::~Camera() {}

void Camera::doUpdate() {}

vect<float> Camera::getPosition() {  
    vect<float> ret = {0, 0};

    if (isFollowing) {
        ret = {following->getWorldX() + (following->getWorldW() / 2),
                following->getWorldY() + (following->getWorldH() / 2)};
    } else {
        ret = position;
    }
    return ret;
}

float Camera::getZoom() {
    return zoom;
}

void Camera::setZoom(float _zoom) {
    zoom = _zoom;
}

void Camera::setPosition(vect<float> _position) {
    position = _position;
}

void Camera::setFollowing(WorldComponent* wc) {
    following = wc;
    isFollowing = true;
}

void Camera::stopFollowing() {
    isFollowing = false;
}