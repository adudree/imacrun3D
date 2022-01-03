
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <string>
#include <memory>

struct Vertex2DUV {
    glm::vec2 position;
    glm::vec2 coordTexture;

    Vertex2DUV();
    Vertex2DUV(glm::vec2 pos, glm::vec2 text){
        position = pos;
        coordTexture = text;
    };
};

class Text 
{
private:
    std::string m_name;
    std::unique_ptr<glimac::Image> m_img;
    glm::vec2 m_position;
    glm::vec2 m_dimensions;
    GLuint m_vbo;
    GLuint m_ibo; 
    GLuint m_vao; 
    GLuint m_texture; 
    

    void setVBO(); 
    void setIBO();
    void setVAO();
    void setTexture();


public:
    Text(std::string text, const glm::vec2 &pos); 
    ~Text();

    bool isClicked = false;

    void init();
    void draw();
    void clickOnText(); 

    void action(); 

    inline const glm::vec2 getPosition() { return m_position;}
    inline const glm::vec2 getDimensions() { return m_dimensions;}
};