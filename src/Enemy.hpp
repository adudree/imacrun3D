#pragma once

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Map.hpp"
#include "Model.hpp"
#include "Player.hpp"
#include "glimac/glm.hpp"

class Enemy {
private:
    glm::vec3       m_position = glm::vec3(0);
    Model           m_model;
    glimac::Program m_program = glimac::loadProgram("assets/shaders/Model.vs.glsl", "assets/shaders/Model.fs.glsl");

public:
    Enemy()
        : m_model("assets/models/enemy/StarSparrow2.obj") {}
    ~Enemy() = default;

    // Getter
    inline const glm::vec3 getPosition() const { return m_position; }

    // Setter
    inline void setPosition(const glm::vec3& pos) { m_position = pos; }

    void draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix, const glm::mat4& modPlayerMat);

    glm::mat4 rotateEnemy(glm::mat4& matrice, const float& alpha);

    void update(glm::vec3 PlayerPosition);

};
