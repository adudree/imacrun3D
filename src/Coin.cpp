#include "Coin.hpp"

/* A FAIRE

    INITIALISATION
    - Placer les pièces sur les tuiles simples OK
        - Si pièce simple alors position pièce centre de la tuile OK
    - Dessiner les pièces (sphère puis forme pièce) OK MAIS ATTENTION DECENTRE : FONCTION SPHERE NUL

    BOUCLE
    - Contact entre joueur et pièce
        - Détection de la collision
        - Disparition pièce
        - Ajout point au score du joueur

*/

/* CONSIGNES
Différentes valeurs de pièces
Position des pièces dans le fichier de la map ?
Lorsque l’explorateur passe sur une pièce, celle-ci disparaı̂t et le score du joueur est augmenté de la
valeur de la pièce (que vous déterminerez).
*/

void Coin::setPosition(const Map& map, float tileWidth, float tileLength)
{
    if (map.getTypeTile(glm::vec2(round(m_position.x / tileWidth), round(m_position.z / tileLength))) == 'S') {
        m_position = glm::vec3{tileWidth / 2, -0.3f, tileLength / 2};
    }
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

// ---------------------------------------------------------------------------- //

// std::vector<ShapeVertex> Coin::buildVertices()
// {
//     return m_sphere.getVertices();
// }

// void Coin::buildVAO()
// {
//     glBindVertexArray(*m_vao);
//     glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);

//     const GLuint VERTEX_ATTR_POSITION  = 0;
//     const GLuint VERTEX_ATTR_NORMAL    = 1;
//     const GLuint VERTEX_ATTR_TEX_COORD = 2;

//     glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
//     glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
//     glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORD);

//     glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
//     glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//     glVertexAttribPointer(VERTEX_ATTR_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }

// void Coin::draw()
// {
//     glBindVertexArray(*m_vao);
//     glDrawArrays(GL_TRIANGLES, 0, m_sphere.getVertexCount());
//     glBindVertexArray(0);
// }
