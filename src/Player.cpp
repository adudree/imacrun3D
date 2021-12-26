#include "Player.hpp"

bool Player::canMoveRight(float tilePosition, float tileWidth)
{
    return m_position.x <= tileWidth * tilePosition + tileWidth / 2 - m_speed * 0.2;
}

bool Player::canMoveLeft(float tilePosition, float tileWidth)
{
    return m_position.x >= tileWidth * tilePosition - tileWidth / 2 + m_speed * 0.2;
}

void Player::fallingTest()
{
    if (m_position.y > 1) // axe vertical inversé tkt
        isFalling = true;
    else
        isFalling = false;
}

void Player::jump()
{
    isJumping      = true;
    m_jumpInitialZ = m_position.z;
}

void Player::updateJump()
{
    float v0    = 10.0f;
    float alpha = M_PI / 3;
    float g     = 15.0f;
    float z     = m_position.z - m_jumpInitialZ;

    if (isJumping) {
        m_position.y = (g * z * z) / (2 * v0 * v0 * cos(alpha) * cos(alpha)) - (tan(alpha) * z) - 1;
        if (m_position.y > -0.9999f) {
            isJumping    = false;
            m_position.y = -1.0f;
        }
    }
}

void Player::update()
{
    updateJump();
    moveForward();
}

/*
Appuie sur touche z
Fonction jump()
tant que isJumping (== m_position.y != 0.0f) --> appel fonction jump
puis on arrête
*/