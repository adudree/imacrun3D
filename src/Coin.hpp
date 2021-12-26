#pragma once

#include <glimac/glm.hpp>
#include <iostream>
#include <vector>
#include "Map.hpp"
#include "Model.hpp"
#include "Tile.hpp"

class Coin {
private:
    int       m_point;
    glm::vec3 m_position;

    /*      Sphere m_sphere;

     VBO<ShapeVertex> m_vbo;
    VAO<ShapeVertex> m_vao;

     GLuint m_texture;

    std::vector<ShapeVertex> buildVertices();
    void                     buildVAO();
    void                     setTexture(); */
    Model           m_model;
    glimac::Program m_program = glimac::loadProgram("assets/shaders/Model.vs.glsl", "assets/shaders/Model.fs.glsl");

public:
    explicit Coin()
        : m_point(1), m_position(glm::vec3(0.f)), m_model("assets/models/coin/asteroid_2.obj")
    {
        //buildVAO();
    }

    Coin(const Coin&) = default;
    Coin& operator=(const Coin&) = default;
    ~Coin()                      = default;

    inline glm::vec3 getPosition() const { return m_position; }

    void setPosition(const Map& map, float tileWidth, float tileLength);

    void draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix);

    bool isCollision(const Player& player) const;

    void touchCoin(Player player);
};