#include "CameraThirdPerson.hpp"
#include <cmath>
#include "glm/gtx/polar_coordinates.hpp"

glm::mat4 CameraThirdPerson::computeMatrix(const glm::vec3& playerPosition) const
{
    const auto cameraPosition = playerPosition - m_zoom * glm::euclidean(glm::vec2{m_tilt, m_pan});
    return glm::lookAt(cameraPosition, playerPosition, {0.f, -glm::sign(glm::cos(m_tilt)), 0.f});
}

// Fonctions mouvements caméra

void CameraThirdPerson::variationPan(float variation)
{
    m_pan += variation * m_vitesseRotation;
}

void CameraThirdPerson::variationTilt(float variation)
{
    if ((canTiltHaut() && variation < 0) ||
        (canTiltBas() && variation > 0)) {
        m_tilt += variation * m_vitesseRotation;
    }
}

void CameraThirdPerson::zoom_avant()
{
    m_zoom *= m_vitesseZoom;
}

void CameraThirdPerson::zoom_arriere()
{
    m_zoom /= m_vitesseZoom;
}

bool CameraThirdPerson::canTiltHaut()
{
    return m_tilt > 0;
}

bool CameraThirdPerson::canTiltBas()
{
    return m_tilt < M_PI / 4;
}