#pragma once

#include "common.hpp"

namespace glimac {

class Tile {
    private:
        std::vector<ShapeVertex> m_Vertices;    // Sommets
        GLsizei m_nVertexCount;                 // Nombre de sommets

        GLuint m_vbo; 
        GLuint m_ibo;
        GLuint m_vao; 

        GLfloat m_posX;
        GLfloat m_posY; 

        void build(GLfloat width, GLfloat height);
        void mainVBO();
        void mainIBO();
        void mainVAO();

    public:
        Tile(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height)
        : m_nVertexCount(0), m_posX(posX), m_posY(posY) 
        {

            build(width, height);   // Construction (voir le .cpp)

            GLuint vbo; 
            GLuint ibo;
            GLuint vao; 
            
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ibo);
            glGenVertexArrays(1, &vao);

            m_vbo = vbo; 
            m_ibo = ibo; 
            m_vao = vao; 

            mainVBO();
            mainIBO();
            mainVAO();


        }
        ~Tile() = default;
        void drawTile(GLuint texture);     
        
        inline const ShapeVertex* getDataPointer() const {return &m_Vertices[0];}
        inline GLsizei getVertexCount() const {return m_nVertexCount;}

        inline GLint getVBO() const {return m_vbo;}
        inline GLint getIBO() const {return m_ibo;}
        inline GLint getVAO() const {return m_vao;}
        
        inline glm::vec2 getPosition() const {return glm::vec2(m_posX, m_posY);}
        
};
    
}