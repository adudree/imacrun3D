#include "Player.hpp"

void Player::draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix)
{
    GLint locMVPMatrix    = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix");
    GLint locMVMatrix     = glGetUniformLocation(m_program.getGLId(), "uMVMatrix");
    GLint locNormalMatrix = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix");
    GLint locModelMatrix  = glGetUniformLocation(m_program.getGLId(), "uModel");
    GLint locTexture      = glGetUniformLocation(m_program.getGLId(), "texture_diffuse1");

    glm::mat4 ProjMatrix = projMatrix;
    glm::mat4 MVMatrix   = mvMatrix;

    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 modMatrix =
        glm::translate(glm::mat4(1), m_position) *
        glm::rotate(glm::mat4(1.), glm::radians(180.0f), glm::vec3(0., 0., 1.)) *
        glm::scale(glm::mat4(1.), glm::vec3(0.1, 0.1, 0.1));

    m_program.use();
    glUniformMatrix4fv(locModelMatrix, 1, GL_FALSE, glm::value_ptr(modMatrix));
    glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniform1i(locTexture, 0);
    m_model.Draw(m_program);
}

void Player::moveForward()
{
    switch (m_orientation) {
    case 'N':
    default:
        m_position.z += m_speed * 0.1;
        break;

    case 'O':
        m_position.x -= m_speed * 0.1;
        break;

    case 'S':
        m_position.z -= m_speed * 0.1;
        break;

    case 'E':
        m_position.x += m_speed * 0.1;
        break;
    }
}

bool Player::canMoveRight(float tilePosition)
{  
    switch (m_orientation) {
    case 'N':
    default:
        return m_position.x <= tilesW * tilePosition + tilesW / 2 - 0.3;
        break;

    case 'O':
        return m_position.z <= tilesL * tilePosition + tilesL / 2 - 0.3;
        break;

    case 'S':
        return m_position.x >= tilesW * tilePosition - tilesW / 2 + 0.3;
        break;

    case 'E':
        return m_position.z >= tilesL * tilePosition - tilesL / 2 + 0.3;
        break;
    }
}

bool Player::canMoveLeft(float tilePosition)
{
    switch (m_orientation) {
    case 'N':
    default:
        return m_position.x >= tilesW * tilePosition - tilesW / 2 + 0.3;
        break;

    case 'O':
        return m_position.z >= tilesL * tilePosition - tilesL / 2 + 0.3;
        break;

    case 'S':
        return m_position.x <= tilesW * tilePosition + tilesW / 2 - 0.3;
        break;

    case 'E':
        return m_position.z <= tilesL * tilePosition + tilesL / 2 - 0.3;
        break;
    }    
}

void Player::moveRight()
{
    switch (m_orientation) {
    case 'N':
    default:
        m_position.x += tilesW / 2 - 0.2;
        break;

    case 'O':
        m_position.z += tilesL / 2 - 0.2;
        break;

    case 'S':
        m_position.x -= tilesW / 2 - 0.2;
        break;

    case 'E':
        m_position.z -= tilesL / 2 - 0.2;
        break;
    }
}

void Player::moveLeft()
{
    switch (m_orientation) {
    case 'N':
    default:
        m_position.x -= tilesW / 2 - 0.2;
        break;

    case 'O':
        m_position.z -= tilesL / 2 - 0.2;
        break;

    case 'S':
        m_position.x += tilesW / 2 - 0.2;
        break;

    case 'E':
        m_position.z += tilesL / 2 - 0.2;
        break;
    }
}

void Player::fall()
{
    if (m_position.y > 1) // axe vertical inversé
        m_isFalling = true;

    m_position.y += m_speed * 0.1;
}

void Player::jump()
{
    m_isJumping      = true;

    switch (m_orientation) {
    case 'N':
    case 'S':
    default:
        m_jumpInitialZ = m_position.z;
        break;

    case 'O':
    case 'E':
        m_jumpInitialZ = m_position.x;
        break;
    }        
}

void Player::bendDown()
{
    m_isDown = !m_isDown;

    if (m_isDown)
        m_position.y = -0.1;
    else
        m_position.y = -0.5;    
}

void Player::updateJump()
{
    float v0    = 10.0f;
    float alpha = M_PI / 3;
    float g     = 15.0f;
    float z;

    switch (m_orientation) {
    case 'N':
    default:
        z = m_position.z - m_jumpInitialZ;
        break;
    case 'S':
        z = m_position.z + m_jumpInitialZ;
        break;

    case 'O':
        z = m_position.x - m_jumpInitialZ;
        break;

    case 'E':
        z = m_position.x + m_jumpInitialZ;
        break;
    }

    if (m_isJumping) {
        m_position.y = (g * z * z) / (2 * v0 * v0 * cos(alpha) * cos(alpha)) - (tan(alpha) * z) - 1;
        if (m_position.y > -0.9999f) {
            m_isJumping    = false;
            m_position.y = -1.0f;
        }
    }
}

void Player::update()
{
    updateJump();
    moveForward();
}