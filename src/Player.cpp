#include "Player.hpp"


// TO DO : à optimiser ici 
bool Player::canMoveRight(float tilePosition, float tileWidth)
{
    if (m_position.x <= tileWidth * tilePosition + tileWidth/2 - m_speed * 0.2) return true;
    else return false;
}

bool Player::canMoveLeft(float tilePosition, float tileWidth)
{
    if (m_position.x >= tileWidth * tilePosition - tileWidth/2 + m_speed * 0.2) return true;
    else return false;
}

void Player::fallingTest()
{
    if (m_position.y > 1) // axe vertical inversé tkt 
        isFalling = true;
    else isFalling = false;
}

void Player::jump()
{
}
