
#include "glimac/Tile.hpp"

namespace glimac {

void Tile::setTexture()
{
    std::unique_ptr<Image> image = loadImage("./src/assets/textures/cardinale.jpg");
    createTexture(m_texture, image);
}

void Tile::build(GLfloat &width, GLfloat &height) {

    ShapeVertex NO, NE, SO, SE; 

    NE.position = glm::vec3(m_posX + width/2, 0, m_posY + height/2);
    SO.position = glm::vec3(m_posX - width/2, 0, m_posY - height/2);
    NO.position = glm::vec3(m_posX - width/2, 0, m_posY + height/2);
    SE.position = glm::vec3(m_posX + width/2, 0, m_posY - height/2);

    SO.texCoords = glm::vec2(0, 1);
    SE.texCoords = glm::vec2(1, 1);
    NO.texCoords = glm::vec2(0, 0);
    NE.texCoords = glm::vec2(1, 0);

    NO.normal = glm::vec3(0, 1, 0);
    NE.normal = glm::vec3(0, 1, 0);
    SO.normal = glm::vec3(0, 1, 0);
    SE.normal = glm::vec3(0, 1, 0);
    
    m_Vertices.push_back(SO);
    m_Vertices.push_back(NO);
    m_Vertices.push_back(NE);
    m_Vertices.push_back(SE);

    m_nVertexCount = m_Vertices.size();
}

void Tile::mainVBO()
{
    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_nVertexCount * sizeof(ShapeVertex), &m_Vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Tile::mainIBO()
{
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    uint32_t indicesRectangle[] = {0, 1, 2, 0, 2, 3};
    
    int sizeTabIBO = sizeof(indicesRectangle)/sizeof(indicesRectangle[0]); 

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeTabIBO * sizeof(uint32_t), indicesRectangle, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Tile::mainVAO() 
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEX_COORD = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORD);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), 0);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glVertexAttribPointer(VERTEX_ATTR_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*) (6 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Tile::drawTile() {
    glBindVertexArray(m_vao);

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindVertexArray(0);
}

bool Tile::PassageOK(Player &p) {
    
    if (p.getPosition().y > m_posPlayerYMin && p.getPosition().y < m_posPlayerYMax) 
    {
        return true;
    }

    return false;
}

}
