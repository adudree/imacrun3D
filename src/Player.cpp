#include "Player.hpp"

void Player::draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix){

    GLint locMVPMatrix    = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix");
    GLint locMVMatrix     = glGetUniformLocation(m_program.getGLId(), "uMVMatrix");
    GLint locNormalMatrix = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix");
    GLint locModelMatrix = glGetUniformLocation(m_program.getGLId(), "uModel");
    GLint locTexture      = glGetUniformLocation(m_program.getGLId(), "texture_diffuse1");

    glm::mat4 ProjMatrix = projMatrix;
    glm::mat4 MVMatrix = mvMatrix;
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 modMatrix = glm::rotate(glm::mat4(1.),glm::radians(180.0f), glm::vec3(0.,0.,1.)) * glm::translate(glm::mat4(1.), m_position) * glm::scale(glm::mat4(1.), glm::vec3(0.1,0.1,0.1));

    m_program.use();
    glUniformMatrix4fv(locModelMatrix, 1, GL_FALSE, glm::value_ptr(modMatrix));  
    glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniform1i(locTexture, 0);
    m_model.Draw(m_program);
}

bool Player::canMoveRight(float tilePosition, float tileWidth)
{
    return m_position.x <= tileWidth * tilePosition + tileWidth / 2 - m_speed * 0.2;
}

bool Player::canMoveLeft(float tilePosition, float tileWidth)
{
    return m_position.x >= tileWidth * tilePosition - tileWidth / 2 + m_speed * 0.2;
}

void Player::fall()
{
    if (m_position.y > 1) // axe vertical inversé
        isFalling = true;

    m_position.y += m_speed * 0.1;
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