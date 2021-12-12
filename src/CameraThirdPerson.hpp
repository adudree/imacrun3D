#pragma once

#include <glimac/glm.hpp>
#include "ICamera.hpp"

class CameraThirdPerson : public ICamera {
public:
    glm::mat4 computeMatrix(const glm::vec3& playerPosition) const override;

    //mouvement camera
    void tourne_droite() override;
    void tourne_gauche() override;
    void tourne_haut() override;
    void tourne_bas() override;
    void zoom_avant();
    void zoom_arriere();

private:
    float m_pan  = 0.f;
    float m_tilt = 0.3f;
    float m_zoom = 10.f;

    float m_vitesseRotation = 0.02f;
    float m_vitesseZoom     = 0.8f;
};