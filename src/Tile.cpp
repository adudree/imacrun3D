
#include "Tile.hpp"

void Tile::setTexture()
{
    std::unique_ptr<glimac::Image> image = glimac::loadImage("bin/assets/textures/cardinale.jpg");
    createTexture(m_texture, image);
}

std::vector<ShapeVertex> Tile::buildVertices()
{
    std::vector<ShapeVertex> vertices;
    ShapeVertex              NO, NE, SO, SE;

    NE.position = glm::vec3(m_posX + m_width / 2, 0, m_posY + m_height / 2);
    SO.position = glm::vec3(m_posX - m_width / 2, 0, m_posY - m_height / 2);
    NO.position = glm::vec3(m_posX - m_width / 2, 0, m_posY + m_height / 2);
    SE.position = glm::vec3(m_posX + m_width / 2, 0, m_posY - m_height / 2);

    SO.texCoords = glm::vec2(0, 1);
    SE.texCoords = glm::vec2(1, 1);
    NO.texCoords = glm::vec2(0, 0);
    NE.texCoords = glm::vec2(1, 0);

    NO.normal = glm::vec3(0, 1, 0);
    NE.normal = glm::vec3(0, 1, 0);
    SO.normal = glm::vec3(0, 1, 0);
    SE.normal = glm::vec3(0, 1, 0);

    vertices.push_back(SO);
    vertices.push_back(NO);
    vertices.push_back(NE);
    vertices.push_back(SE);

    return vertices;
}

std::vector<uint32_t> Tile::buildIndices()
{
    return {0, 1, 2, 0, 2, 3};
}

void Tile::buildVAO()
{
    glBindVertexArray(*m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ibo);
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

void Tile::drawTile()
{
    glBindVertexArray(*m_vao);

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}

// bool Tile::PassageOK(Player& p)
// {
//     if (p.getPosition().y > m_posPlayerXMin && p.getPosition().y < m_posPlayerXMax) {
//         return true;
//     }

//     return false;
// }
