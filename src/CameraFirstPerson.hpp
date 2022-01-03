#pragma once

#include <glimac/glm.hpp>
#include "ICamera.hpp"

class CameraFirstPerson : public ICamera {
public:
    glm::mat4 computeMatrix(const glm::vec3& playerPosition) const override;
    void      variationPan(float variation) override;
    void      variationTilt(float variation) override;
    void      turnPan(float variation);
    void      resetOffset();

private:
    float                  m_pan             = 0.f;
    float                  m_tilt            = 0.3f;
    float                  m_offsetPan       = 0.0f;
    static constexpr float m_vitesseRotation = 0.002f;

    bool canPanLeft();
    bool canPanRight();
    bool canTiltUp();
    bool canTiltDown();
};
