#include "Coin.hpp"

/* A FAIRE

    INITIALISATION
    - Placer les pièces sur les tuiles simples
        - Si pièce simple alors position pièce centre de la tuile
    - Dessiner les pièces (sphère puis forme pièce) OK

    BOUCLE
    - Contact entre joueur et pièce
        - Détection de la collision VERIF
        - Disparition pièce VERIF
        - Ajout point au score du joueur VERIF

*/

/* CONSIGNES
Différentes valeurs de pièces
Position des pièces dans le fichier de la map ?
Lorsque l’explorateur passe sur une pièce, celle-ci disparaı̂t et le score du joueur est augmenté de la
valeur de la pièce (que vous déterminerez).
*/

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

bool Coin::isCollision(const glm::vec3& posPlayer) // A OPTIMISER !!!
{
    if ((posPlayer.z <= (m_position.z + 0.5f)) &&
        (posPlayer.z >= (m_position.z - 0.5f)) &&
        (posPlayer.x <= (m_position.x + 0.5f)) &&
        (posPlayer.x >= (m_position.x - 0.5f)) &&
        (posPlayer.y <= (m_position.y + 0.5f)) &&
        (posPlayer.y >= (m_position.y - 0.5f))) {
        m_isCollected = true;
        return true;
    }
    else {
        return false;
    }

    /*     return  (posPlayer.z <= (m_position.z + 0.5f)) &&
                (posPlayer.z >= (m_position.z - 0.5f)) &&
                (posPlayer.x <= (m_position.x + 0.5f)) &&
                (posPlayer.x >= (m_position.x - 0.5f)) &&
                (posPlayer.y <= (m_position.y + 0.5f)) &&
                (posPlayer.y >= (m_position.y - 0.5f)); */
}

void createCoins(Map& map, std::vector<std::unique_ptr<Coin>>& coins)
{
    for (int i = 0; i < map.getDimensions()[0]; i++) {
        for (int j = 0; j < map.getDimensions()[1]; j++) {
            float hCoin = 0;
            switch (map.getTypeTile(glm::vec2(i, j))) {
            case 'S': hCoin = -0.7; break;
            case 'H': hCoin = -1.0f; break;
            case 'A': hCoin = -0.2f; break;
            default: break;
            }
            if (hCoin != 0)
                coins.push_back(std::make_unique<Coin>(glm::vec3(i * tilesW, hCoin, j * tilesL)));
        }
    }
}