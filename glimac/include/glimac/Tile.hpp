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

        void build(GLfloat posX, GLfloat posY, GLsizei width, GLsizei height);

    public:
        Tile(GLfloat posX, GLfloat posY, GLsizei width, GLsizei height, GLuint vbo, GLuint ibo, GLuint vao): m_nVertexCount(0), m_vbo(vbo), m_ibo(ibo), m_vao(vao)
        {
            build(posX, posY, width, height);   // Construction (voir le .cpp)
        }
        ~Tile() = default;
        
        inline const ShapeVertex* getDataPointer() const {return &m_Vertices[0];}
        inline GLsizei getVertexCount() const {return m_nVertexCount;}

        inline GLint getVBO() const {return m_vbo;}
        inline GLint getIBO() const {return m_ibo;}
        inline GLint getVAO() const {return m_vao;}

        
        void mainVBO();
        void mainIBO();
        void mainVAO();
};
    
}