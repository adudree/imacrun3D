#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <iostream>

#include "ShapeVertex.hpp"
#include "glimac/Image.hpp"
#include "Texture.hpp"

class Tile {
    protected:

        std::vector<ShapeVertex> m_Vertices;    // Sommets
        GLsizei m_nVertexCount;                 // Nombre de sommets

        GLuint m_vbo; 
        GLuint m_ibo;
        GLuint m_vao; 

        GLfloat m_posX;
        GLfloat m_posY; 

        // positions entre lesquelles le joueur peut circuler
        // généralement les bords de la tuile  
        // changent lorsque obstacle (objet ou trou) sur la tuile
        // ex : trou à gauche de la tuile 
        // si ymin est dépassé, le joueur tombe dans le trou
        // idem si ymax est dépassé pour trou à droite de la tuile
        // pour tuile hole (toute la tuile est un trou) : différent 
        // pas de y min ou max, le joueur est obligé de sauter 
        GLfloat m_posPlayerYMin;
        GLfloat m_posPlayerYMax; 


        GLuint m_texture; 

        void build(GLfloat width, GLfloat height);
        void mainVBO();
        void mainIBO();
        void mainVAO();

        void setTexture();


    public:
        Tile(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height, GLuint &texture)
        : m_nVertexCount(0), m_posX(posX), m_posY(posY), m_texture(texture)
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
        void drawTile();     
        
        inline const ShapeVertex* getDataPointer() const {return &m_Vertices[0];}
        inline GLsizei getVertexCount() const {return m_nVertexCount;}

        inline GLint getVBO() const {return m_vbo;}
        inline GLint getIBO() const {return m_ibo;}
        inline GLint getVAO() const {return m_vao;}
        
        inline glm::vec2 getPosition() const {return glm::vec2(m_posX, m_posY);}
        
};
