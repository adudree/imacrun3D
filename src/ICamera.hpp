#pragma once

#include <glimac/glm.hpp>

class ICamera {
public:
    virtual glm::mat4 computeMatrix(const glm::vec3& playerPosition) const = 0;
    virtual void      tourne_droite()                                      = 0;
    virtual void      tourne_gauche()                                      = 0;
    virtual void      tourne_haut()                                        = 0;
    virtual void      tourne_bas()                                         = 0;
};