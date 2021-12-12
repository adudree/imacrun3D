#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "IBO.hpp"
#include "ShapeVertex.hpp"
#include "Texture.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "glimac/Image.hpp"

class Tile {
protected:
    GLfloat m_posX;
    GLfloat m_posY;

    GLfloat m_width;
    GLfloat m_height;

    VBO<ShapeVertex> m_vbo;
    IBO              m_ibo;
    VAO<ShapeVertex> m_vao;

    // positions entre lesquelles le joueur peut circuler
    // généralement les bords de la tuile
    // changent lorsque obstacle (objet ou trou) sur la tuile
    // ex : trou à gauche de la tuile
    // si ymin est dépassé, le joueur tombe dans le trou
    // idem si ymax est dépassé pour trou à droite de la tuile
    // pour tuile hole (toute la tuile est un trou) : différent
    // pas de y min ou max, le joueur est obligé de sauter
    GLfloat m_posPlayerXMin;
    GLfloat m_posPlayerXMax;

    GLuint m_texture;

    std::vector<ShapeVertex> buildVertices();
    std::vector<uint32_t>    buildIndices();
    void                     buildVAO();

    void setTexture();

public:
    Tile(GLfloat posX, GLfloat posY, GLfloat width, GLfloat height, GLuint texture)
        : m_posX(posX), m_posY(posY), m_width(width), m_height(height), m_vbo(buildVertices()), m_ibo(buildIndices()), m_vao(), m_texture(texture)
    {
        buildVAO();
    }
    ~Tile() = default;
    void drawTile();

    inline GLint getWidth() const { return m_width; }
    inline GLint getHeight() const { return m_height; }

    inline GLuint getVBO() const { return *m_vbo; }
    inline GLuint getIBO() const { return *m_ibo; }
    inline GLuint getVAO() const { return *m_vao; }

    inline glm::vec2 getPosition() const { return glm::vec2(m_posX, m_posY); }

    // PassageOK : si le joueur respecte certaines conditions
    // ex : est baissé et/ou est en train de sauter
    // et/ou est compris entre ymin et ymax
    // bool PassageOK(Player& player);
};
