/* 

Contrôle de la caméra

Le jeu doit contenir deux types de caméra :

— une caméra centrée sur l’explorateur, qui permet de tourner autour et de zoomer à l’aide de la
souris ;

— une caméra permettant de voir à travers les yeux de l’explorateur et offrant la possibilité de tourner
la tête à l’aide de la souris (attention, nous ne sommes pas dans l’Exorciste, les déplacements de
la tête doivent être limités).

À tout moment, le joueur peut changer de vue en appuyant sur la touche C et bloquer la caméra dans
une configuration idéale pour jouer avec la touche L.

*/

#include "CameraThirdPerson.hpp"
#include <cmath>
#include "glm/gtx/polar_coordinates.hpp"

glm::mat4 CameraThirdPerson::computeMatrix(const glm::vec3& playerPosition) const
{
    const auto cameraPosition = playerPosition - m_zoom * glm::euclidean(glm::vec2{m_tilt, m_pan});
    return glm::lookAt(cameraPosition, playerPosition, {0.f, -glm::sign(glm::cos(m_tilt)), 0.f});
}

// Fonctions mouvements caméra

void CameraThirdPerson::tourne_droite()
{
    m_pan -= m_vitesseRotation;
}

void CameraThirdPerson::tourne_gauche()
{
    m_pan += m_vitesseRotation;
}

void CameraThirdPerson::tourne_haut()
{
    m_tilt += m_vitesseRotation;
}

void CameraThirdPerson::tourne_bas()
{
    m_tilt -= m_vitesseRotation;
}

void CameraThirdPerson::zoom_avant()
{
    m_zoom *= m_vitesseZoom;
}

void CameraThirdPerson::zoom_arriere()
{
    m_zoom /= m_vitesseZoom;
}