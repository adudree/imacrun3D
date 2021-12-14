#pragma once

#include <glimac/glm.hpp>
#include "ICamera.hpp"

class CameraFirstPerson : public ICamera {
public:
    glm::mat4 computeMatrix(const glm::vec3& playerPosition) const override;

    //mouvement camera
    void variationPan(float variation) override;
    void variationTilt(float variation) override;

private:
    float m_pan  = 0.f;
    float m_tilt = 0.3f;

    float m_vitesseRotation = 0.002f;

    bool canPanGauche();
    bool canPanDroite();
    bool canTiltHaut();
    bool canTiltBas();
};