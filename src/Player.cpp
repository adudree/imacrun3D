#include "Player.hpp"


// TO DO : à optimiser ici 
bool Player::canMoveRight(float tilePosition, float tileWidth)
{
    // if (m_position.x <= tileWidth * tilePosition + tileWidth / 2 - m_speed * 0.2)
    //     return true;
    // else
    //     return false;
    return m_position.x <= tileWidth * tilePosition + tileWidth / 2 - m_speed * 0.2;
}

bool Player::canMoveLeft(float tilePosition, float tileWidth)
{
    // if (m_position.x >= tileWidth * tilePosition - tileWidth / 2 + m_speed * 0.2)
    //     return true;
    // else
    //     return false;
    return m_position.x >= tileWidth * tilePosition - tileWidth / 2 + m_speed * 0.2;
}

void Player::fallingTest()
{
    if (m_position.y > 1) // axe vertical inversé tkt 
        isFalling = true;
    else isFalling = false;
}


void Player::jump()
{
    // y = (-g / (2 * v0^2 * cos(alpha))) * x^2 + tan(alpha) * x + h
    // v0
    // alpha
    // g
    // h
    // x (variable)

    float v0    = 0.5f;
    float alpha = M_PI / 3;
    float g     = 9.81f;

    m_position.y += (-g / (2 * v0 * v0 * cos(alpha))) * m_position.x * m_position.x + tan(alpha) * m_position.x;

    // float x     = m_position.x;
    // float v0  qqq  = 1;
    // float alpha = 45;
    // // alpha et v0 à définir et calculer
    // float y      = -9.81 * x * x / (v0 * v0 * 2 * cos(alpha) * cos(alpha)) + x * tan(alpha);
    // m_position.y = y;

    // y = - g * x*x / (2 * v0*v0 * cos(alpha)*cos(alpha)) * x * tan(alpha)
    // g = 9.81
    // v0 = vecteur directionnel là // faut le définir pour que la parabole soit bien
    // alpha : angle (degré)
}