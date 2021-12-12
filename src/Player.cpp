#include "Player.hpp"

/*
void Player::collision(Coin &coin)
{
    if(m_position == coin.m_position)
    {
        coin.disappear();
        score++; 
    }
}
*/

void Player::collision(Hole& /*Obstacle*/)
{
    if (!isJumping)
        m_position.y--;
}

bool Player::isFalling()
{
    if (m_position.y < -5)
        return true;
    return false;
}

bool Player::isOnTile(Tile& tile)
{
    if (m_position.z - tile.getPosition().y < abs(tile.getHeight() / 2))
        return true;
    else
        return false;
}

/*
void Player::collision(Arch& Obstacle)
{
    // si le joueur est sur la tuile mais pas baissé
    // il n'avance plus vers l'avant

    // A TESTER AILLEURS : si sa position = celle des singes, c perdu
}
*/

void Player::moveSide(const float& indice)
{
    // indice > 0 : vers la droite
    // indice < 0 : vers la gauche
    m_position.x += indice;
}

void Player::jump()
{
    float x     = m_position.x;
    float v0    = 1;
    float alpha = 45;
    // alpha et v0 à définir et calculer
    float y      = -9.81 * x * x / (v0 * v0 * 2 * cos(alpha) * cos(alpha)) + x * tan(alpha);
    m_position.y = y;

    // y = - g * x*x / (2 * v0*v0 * cos(alpha)*cos(alpha)) * x * tan(alpha)
    // g = 9.81
    // v0 = vecteur directionnel là // faut le définir pour que la parabole soit bien
    // alpha : angle (degré)
}
