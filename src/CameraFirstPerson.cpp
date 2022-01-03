#include "CameraFirstPerson.hpp"
#include <cmath>
#include "glm/gtx/polar_coordinates.hpp"

// Camera direction

glm::mat4 CameraFirstPerson::computeMatrix(const glm::vec3& playerPosition) const
{
    return glm::lookAt(playerPosition, playerPosition + glm::euclidean(glm::vec2{m_tilt, m_pan + m_offsetPan}), {0.f, -1.f, 0.f});
}

// Camera movement

void CameraFirstPerson::variationPan(float variation)
{
    if ((canPanRight() && variation > 0) ||
        (canPanLeft() && variation < 0)) {
        m_pan += variation * m_rotationSpeed;
    }
}

void CameraFirstPerson::variationTilt(float variation)
{
    if ((canTiltUp() && variation < 0) ||
        (canTiltDown() && variation > 0)) {
        m_tilt += variation * m_rotationSpeed;
    }
}

// Camera movement in turn

void CameraFirstPerson::turnPan(float variation)
{
    m_offsetPan += variation;
}

void CameraFirstPerson::resetOffset()
{
    m_offsetPan = 0;
}

// Test to block the camera

bool CameraFirstPerson::canPanLeft()
{
    return m_pan > -M_PI / 2;
}

bool CameraFirstPerson::canPanRight()
{
    return m_pan < M_PI / 2;
}

bool CameraFirstPerson::canTiltUp()
{
    return m_tilt > -M_PI / 4;
}

bool CameraFirstPerson::canTiltDown()
{
    return m_tilt < M_PI / 4;
}
