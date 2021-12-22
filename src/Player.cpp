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

glm::vec2 Player::getActiveTile(float tileWidth, float  tileLength) 
{
    return glm::vec2(round(m_position.x / tileWidth), round(m_position.z / tileLength));
}


void Player::tilesConditions(char &tile)
{
    switch (tile)
    {
    case 'P' || 'S':
        // tout est normal 
        break;

    case 'H':
        fall();
        break;
    
    default:
        break;
    }

}

bool Player::isFalling()
{
    if (m_position.y > 1) // axe vertical inversé tkt 
        return true;
    return false;
}

void Player::jump()
{
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


std::vector<ShapeVertex> Player::buildVertices()
{
    return m_sphere.getVertices();
}

void Player::buildVAO()
{
    glBindVertexArray(*m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);

    const GLuint VERTEX_ATTR_POSITION  = 0;
    const GLuint VERTEX_ATTR_NORMAL    = 1;
    const GLuint VERTEX_ATTR_TEX_COORD = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORD);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(VERTEX_ATTR_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Player::draw()
{
    glBindVertexArray(*m_vao);
    glDrawArrays(GL_TRIANGLES,0, m_sphere.getVertexCount());
    glBindVertexArray(0);
}