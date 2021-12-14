#pragma once

#include <glimac/glm.hpp>

class ICamera {
public:
    virtual glm::mat4 computeMatrix(const glm::vec3& playerPosition) const = 0;
    virtual void      variationPan(float variation)                        = 0;
    virtual void      variationTilt(float variation)                       = 0;
};