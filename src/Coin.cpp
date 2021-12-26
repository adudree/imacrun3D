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

void Coin::setPosition(const Map& map, float tileWidth, float tileLength)
{
    if (map.getTypeTile(round(m_position.x / tileWidth), round(m_position.z / tileLength)) == 'S') {
        m_position = glm::vec3{tileWidth / 2, -0.3f, tileLength / 2};
    }
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
