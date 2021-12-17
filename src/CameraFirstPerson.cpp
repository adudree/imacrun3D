/* 

Contrôle de la caméra

Une caméra permettant de voir à travers les yeux de l’explorateur et offrant la possibilité de tourner
la tête à l’aide de la souris (attention, nous ne sommes pas dans l’Exorciste, les déplacements de
la tête doivent être limités).

À tout moment, le joueur peut changer de vue en appuyant sur la touche C et bloquer la caméra dans
une configuration idéale pour jouer avec la touche L.

*/

#include "CameraFirstPerson.hpp"
#include <cmath>
#include <iostream>
#include "glm/gtx/polar_coordinates.hpp"

glm::mat4 CameraFirstPerson::computeMatrix(const glm::vec3& playerPosition) const
{
    return glm::lookAt(playerPosition, playerPosition + glm::euclidean(glm::vec2{m_tilt, m_pan}), {0.f, -1.f, 0.f});
}

// Fonctions mouvements caméra

void CameraFirstPerson::variationPan(float variation)
{
    if ((canPanDroite() && variation > 0) ||
        (canPanGauche() && variation < 0)) {
        m_pan += variation * m_vitesseRotation;
    }
}

void CameraFirstPerson::variationTilt(float variation)
{
    if ((canTiltHaut() && variation < 0) ||
        (canTiltBas() && variation > 0)) {
        m_tilt += variation * m_vitesseRotation;
    }
}

bool CameraFirstPerson::canPanGauche()
{
    return m_pan > -M_PI / 2;
}

bool CameraFirstPerson::canPanDroite()
{
    return m_pan < M_PI / 2;
}

bool CameraFirstPerson::canTiltHaut()
{
    return m_tilt > -M_PI / 4;
}

bool CameraFirstPerson::canTiltBas()
{
    return m_tilt < M_PI / 4;
}
