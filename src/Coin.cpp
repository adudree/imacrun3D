#include "Coin.hpp"

bool Coin::isCollision(const glm::vec3& posPlayer)
{
    return (posPlayer.z <= (m_position.z + 0.5f)) &&
           (posPlayer.z >= (m_position.z - 0.5f)) &&
           (posPlayer.x <= (m_position.x + 0.5f)) &&
           (posPlayer.x >= (m_position.x - 0.5f)) &&
           (posPlayer.y <= (m_position.y + 0.5f)) &&
           (posPlayer.y >= (m_position.y - 0.5f));
}

void Coin::draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix)
{
    GLint locMVPMatrix    = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix");
    GLint locMVMatrix     = glGetUniformLocation(m_program.getGLId(), "uMVMatrix");
    GLint locNormalMatrix = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix");
    GLint locModelMatrix  = glGetUniformLocation(m_program.getGLId(), "uModel");
    GLint locTexture      = glGetUniformLocation(m_program.getGLId(), "texture_diffuse1");

    glm::mat4 ProjMatrix = projMatrix;
    glm::mat4 MVMatrix   = mvMatrix;

    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    m_rotateFloat += 0.7;
    glm::mat4 modMatrix =
        glm::translate(glm::mat4(1), m_position) *
        glm::rotate(glm::mat4(1.), glm::radians(m_rotateFloat), glm::vec3(0., 1., 0.)) *
        glm::scale(glm::mat4(1.), glm::vec3(0.5, 0.5, 0.5));

    m_program.use();
    glUniformMatrix4fv(locModelMatrix, 1, GL_FALSE, glm::value_ptr(modMatrix));
    glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniform1i(locTexture, 0);
    m_model.Draw(m_program);
}

void createCoins(const Map& map, std::vector<std::unique_ptr<Coin>>& coins)
{
    for (int i = 0; i < map.getDimensions()[0]; i++) {
        for (int j = 0; j < map.getDimensions()[1]; j++) {
            float hCoin = 0;
            switch (map.getTypeTile(glm::vec2(i, j))) {
            case 'S': hCoin = -0.9; break;
            case 'H': hCoin = -2.2f; break;
            case 'A': hCoin = -0.6f; break;
            default: break;
            }
            if (hCoin != 0)
                coins.push_back(std::make_unique<Coin>(glm::vec3(i * tilesW, hCoin, j * tilesL)));
        }
    }
}
