#pragma once

#include "common.hpp"

namespace glimac {

class Tile {
    private:
        std::vector<ShapeVertex> m_Vertices;    // Sommets
        GLsizei m_nVertexCount;                 // Nombre de sommets

        void build(GLfloat posX, GLfloat posY, GLsizei width, GLsizei height);

    public:
        Tile(GLfloat posX, GLfloat posY, GLsizei width, GLsizei height): m_nVertexCount(0) 
        {
            build(posX, posY, width, height);   // Construction (voir le .cpp)
        }
        ~Tile() = default;
        
        inline const ShapeVertex* getDataPointer() const {return &m_Vertices[0];}
        inline GLsizei getVertexCount() const {return m_nVertexCount;}
        
};
    
}