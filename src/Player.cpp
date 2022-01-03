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

    float alpha;
    switch (m_orientation) {
    default:
    case 'N': alpha = 0; break;
    case 'E': alpha = 1; break;
    case 'S': alpha = 2; break;
    case 'O': alpha = 3; break;
    }

    modMatrix = rotatePlayer(modMatrix, alpha);

    m_program.use();
    glUniformMatrix4fv(locModelMatrix, 1, GL_FALSE, glm::value_ptr(modMatrix));
    glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniform1i(locTexture, 0);
    m_model.Draw(m_program);
}

// Movement

void Player::moveForward()
{
    switch (m_orientation) {
    default:
    case 'N': m_position.z += m_speed * 0.1; break;
    case 'O': m_position.x -= m_speed * 0.1; break;
    case 'S': m_position.z -= m_speed * 0.1; break;
    case 'E': m_position.x += m_speed * 0.1; break;
    }
}

// Right and Left not in a turn

bool Player::canMoveRight(float tilePosition)
{
    switch (m_orientation) {
    default:
    case 'N': return m_position.x <= tilesW * tilePosition + tilesW / 2 - 0.3; break;
    case 'O': return m_position.z <= tilesL * tilePosition + tilesL / 2 - 0.3; break;
    case 'S': return m_position.x >= tilesW * tilePosition - tilesW / 2 + 0.3; break;
    case 'E': return m_position.z >= tilesL * tilePosition - tilesL / 2 + 0.3; break;
    }
}

bool Player::canMoveLeft(float tilePosition)
{
    switch (m_orientation) {
    default:
    case 'N': return m_position.x >= tilesW * tilePosition - tilesW / 2 + 0.3; break;
    case 'O': return m_position.z >= tilesL * tilePosition - tilesL / 2 + 0.3; break;
    case 'S': return m_position.x <= tilesW * tilePosition + tilesW / 2 - 0.3; break;
    case 'E': return m_position.z <= tilesL * tilePosition + tilesL / 2 - 0.3; break;
    }
}

void Player::moveRight()
{
    switch (m_orientation) {
    default:
    case 'N': m_position.x += tilesW / 2 - 0.2; break;
    case 'O': m_position.z += tilesL / 2 - 0.2; break;
    case 'S': m_position.x -= tilesW / 2 - 0.2; break;
    case 'E': m_position.z -= tilesL / 2 - 0.2; break;
    }
}

void Player::moveLeft()
{
    switch (m_orientation) {
    default:
    case 'N': m_position.x -= tilesW / 2 - 0.2; break;
    case 'O': m_position.z -= tilesL / 2 - 0.2; break;
    case 'S': m_position.x += tilesW / 2 - 0.2; break;
    case 'E': m_position.z += tilesL / 2 - 0.2; break;
    }
}

// Right and Left in a turn

glm::mat4 Player::rotatePlayer(glm::mat4& matrice, const float& alpha)
{
    return glm::rotate(matrice, alpha * glm::radians(90.0f), glm::vec3(0., -1., 0.));
}

// Vertical movement

void Player::verticalInitialize()
{
    switch (m_orientation) {
    default:
    case 'N':
    case 'S': m_InitialZ = m_position.z; break;
    case 'O':
    case 'E': m_InitialZ = m_position.x; break;
    }
    m_InitialY = m_position.y;
}

void Player::jump()
{
    m_isJumping = true;
    verticalInitialize();
}

void Player::down()
{
    m_isDown = true;
    verticalInitialize();
}

void Player::fall()
{
    if (m_position.y > 1) // Inverted axe
        m_isFalling = true;

    m_position.y += m_speed * 0.1;
}

void Player::updateMovement()
{
    float v0;
    float alpha;
    float g;
    float z;

    switch (m_orientation) {
    default:
    case 'N': z = m_position.z - m_InitialZ; break;
    case 'E': z = m_position.x - m_InitialZ; break;
    case 'S': z = m_InitialZ - m_position.z; break;
    case 'O': z = m_InitialZ - m_position.x; break;
    }

    if (m_isJumping) {
        v0    = 10.0f;
        alpha = M_PI / 4;
        g     = 15.0f;

        m_position.y = (g * z * z) / (2 * v0 * v0 * cos(alpha) * cos(alpha)) - (tan(alpha) * z) - 0.5;
        if (m_position.y > m_InitialY) {
            m_position.y = m_InitialY;
            m_isJumping  = false;
        }
    }

    if (m_isDown) {
        v0    = 15.0f;
        alpha = M_PI / 12;
        g     = 20.0f;

        m_position.y = -(g * z * z) / (2 * v0 * v0 * cos(alpha) * cos(alpha)) + (tan(alpha) * z) - 0.5;
        if (m_position.y < m_InitialY) {
            m_position.y = m_InitialY;
            m_isDown     = false;
        }
    }
}

// Final movement

void Player::update()
{
    updateMovement();
    moveForward();
}
