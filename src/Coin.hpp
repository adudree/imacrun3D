#pragma once

#include <glimac/glm.hpp>
#include <iostream>
#include <vector>
#include "Map.hpp"
#include "Sphere.hpp"
#include "Tile.hpp"
#include "VAO.hpp"

class Coin {
private:
    int       m_point;
    glm::vec3 m_position;

    // Sphere m_sphere;

    // VBO<ShapeVertex> m_vbo;
    VAO<ShapeVertex> m_vao;

    // GLuint m_texture;

    std::vector<ShapeVertex> buildVertices();
    void                     buildVAO();
    void                     setTexture();

public:
    explicit Coin()
        : m_point(1), m_position(glm::vec3(0.f))
        // m_sphere(Sphere(1.0f, 8.0f, 8.0f)), 
        // m_vbo(buildVertices()), m_vao(), m_texture(texture)
    {
        buildVAO();
    }

    Coin(const Coin&) = default;
    Coin& operator=(const Coin&) = default;
    ~Coin()                      = default;

    inline glm::vec3 getPosition() const { return m_position; }

    void setPosition(const Map& map, float tileWidth, float tileLength);

    void draw();
};