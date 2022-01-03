#include "Text.hpp"

Text::Text(std::string text, const glm::vec2 &pos)
{
    m_name = text;
    m_position = pos; 
    std::string imgToLoad = "assets/textures/"+ text +".png";
    m_img = glimac::loadImage(imgToLoad);

    m_dimensions = glm::vec2(float(m_img->getWidth()) / 500, float(m_img->getHeight()) / 500);
    std::cout << m_dimensions << std::endl;
}

void Text::init()
{
    setVBO();
    setIBO();
    setVAO();
    setTexture();
}

void Text::setVBO()
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    Vertex2DUV vertices[] = { 
        Vertex2DUV(glm::vec2(m_position.x - m_dimensions.x / 2, m_position.y - m_dimensions.y / 2), glm::vec2(0, 1)),
        Vertex2DUV(glm::vec2(m_position.x - m_dimensions.x / 2, m_position.y + m_dimensions.y / 2), glm::vec2(0, 0)),
        Vertex2DUV(glm::vec2(m_position.x + m_dimensions.x / 2, m_position.y + m_dimensions.y / 2), glm::vec2(1, 0)), 
        Vertex2DUV(glm::vec2(m_position.x + m_dimensions.x / 2, m_position.y - m_dimensions.y / 2), glm::vec2(1, 1))
    };

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Text::setIBO()
{
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    uint32_t indices[] = {0, 1, 2, 0, 2, 3};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Text::setVAO()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);


    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 
        sizeof(Vertex2DUV), 0);
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 2, GL_FLOAT, GL_FALSE, 
        sizeof(Vertex2DUV), (const GLvoid*) offsetof(Vertex2DUV, coordTexture));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);    
    
    glBindVertexArray(0);
}

void Text::setTexture()
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_img->getWidth(), m_img->getHeight(), 0, GL_RGBA, GL_FLOAT, m_img->getPixels());
        
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::draw()
{
    glBindVertexArray(m_vao);
    glBindTexture(GL_TEXTURE_2D, m_texture); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

Text::~Text()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteTextures(1, &m_texture);
}

void Text::clickOnText()
{
    isClicked =  true;
}

void Text::action()
{
    if (m_name == "menu/lancer")    // INIT LE JEU TMTCLANCER
    if (m_name == "menu/quitter")   // INIT LE JEU TMTCLANCER
    if (m_name == "menu/rejouer")   // INIT LE JEU TMTCLANCER
    if (m_name == "menu/reprendre") // INIT LE JEU TMTCLANCER

    //fermer le menu + 
    isClicked = false;
}