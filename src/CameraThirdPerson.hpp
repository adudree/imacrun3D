#pragma once

#include <glimac/glm.hpp>
#include "ICamera.hpp"

class CameraThirdPerson : public ICamera {
public:
    glm::mat4 computeMatrix(const glm::vec3& playerPosition) const override;

    //mouvement camera
    void variationPan(float variation) override;
    void variationTilt(float variation) override;
    void turnPan(float variation);
    void zoom_avant();
    void zoom_arriere();

private:
    float m_pan  = 0.f;
    float m_tilt = 0.3f;
    float m_zoom = 10.f;

    static constexpr float m_vitesseRotation = 0.02f;
    static constexpr float m_vitesseZoom     = 0.8f;

    bool canTiltHaut();
    bool canTiltBas();
};