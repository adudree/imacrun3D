#pragma once

#include <glimac/glm.hpp>
#include "ICamera.hpp"

class CameraThirdPerson : public ICamera {
public:
    glm::mat4 computeMatrix(const glm::vec3& playerPosition) const override;
    void      variationPan(float variation) override;
    void      variationTilt(float variation) override;
    void      turnPan(float variation);
    void      zoomIn();
    void      zoomOut();

private:
    float                  m_pan           = 0.f;
    float                  m_tilt          = 0.3f;
    float                  m_zoom          = 10.f;
    static constexpr float m_rotationSpeed = 0.02f;
    static constexpr float m_zoomSpeed     = 0.8f;

    bool canTiltUp();
    bool canTiltDown();
};
