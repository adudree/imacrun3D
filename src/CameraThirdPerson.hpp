#pragma once 

#include <glimac/glm.hpp>

class CameraThirdPerson {
public:
    glm::mat4 computeMatrix(const glm::vec3& playerPosition) const;

    //mouvement camera
    void tourne_droite();
    void tourne_gauche();
    void tourne_haut();
    void tourne_bas();
    void zoom_avant();
    void zoom_arriere();

private:
    float m_pan = 0.f;
    float m_tilt = 0.3f;
    float m_zoom = 10.f;

    float m_vitesseRotation = 0.02f;
    float m_vitesseZoom = 0.8f;
};