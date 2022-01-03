#include "CameraThirdPerson.hpp"
#include <cmath>
#include "glm/gtx/polar_coordinates.hpp"

// Camera direction

glm::mat4 CameraThirdPerson::computeMatrix(const glm::vec3& playerPosition) const
{
    const auto cameraPosition = playerPosition - m_zoom * glm::euclidean(glm::vec2{m_tilt, m_pan});
    return glm::lookAt(cameraPosition, playerPosition, {0.f, -glm::sign(glm::cos(m_tilt)), 0.f});
}

// Camera movement

void CameraThirdPerson::variationPan(float variation)
{
    m_pan += variation * m_rotationSpeed;
}

void CameraThirdPerson::variationTilt(float variation)
{
    if ((canTiltUp() && variation < 0) ||
        (canTiltDown() && variation > 0)) {
        m_tilt += variation * m_rotationSpeed;
    }
}

// Camera movement in turn

void CameraThirdPerson::turnPan(float variation)
{
    m_pan += variation;
}

// Zoom camera

void CameraThirdPerson::zoomIn()
{
    m_zoom *= m_zoomSpeed;
}

void CameraThirdPerson::zoomOut()
{
    m_zoom /= m_zoomSpeed;
}

// Test to block the camera

bool CameraThirdPerson::canTiltUp()
{
    return m_tilt > 0;
}

bool CameraThirdPerson::canTiltDown()
{
    return m_tilt < M_PI / 4;
}
