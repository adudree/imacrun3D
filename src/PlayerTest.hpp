#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "Hole.hpp"
#include "IBO.hpp"
#include "Map.hpp"
#include "Model.hpp"
#include "Tile.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "glimac/glm.hpp"

class PlayerTest {
private:
    std::string m_nom;
    int         m_score;

    glm::vec3 m_position;

    /*     VBO<ShapeVertex> m_vbo;
        VAO<ShapeVertex> m_vao; */

    Model           m_model;
    glimac::Program m_program = glimac::loadProgram("assets/shaders/Model.vs.glsl", "assets/shaders/Model.fs.glsl");

public:
    PlayerTest()
        : m_nom("John Doe"), m_score(0), m_position(0.5,0.,0.), m_model("assets/models/test2/StarSparrow.obj")
    {
    }
    ~PlayerTest() = default;
    void draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix); // chargement + affichage obj 3D
};