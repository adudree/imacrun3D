#pragma once
#include <stdlib.h>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "Map.hpp"
#include "Model.hpp"
#include "glimac/glm.hpp"

class Arc {
private:
    Model           m_model;
    glm::vec3       m_position;
    std::string     m_pathModel;
    glimac::Program m_program             = glimac::loadProgram("assets/shaders/Model.vs.glsl", "assets/shaders/Model.fs.glsl");
    float           m_randomModifierScale = float((std::rand() % 6) + 4) / 10;
    float           m_randomRotateX       = float(std::rand());
    float           m_randomRotateY       = float(std::rand());
    float           m_randomRotateZ       = float(std::rand());

public:
    Arc(GLfloat posTileX, GLfloat posTileY, std::string type)
        : m_model(type), m_position(glm::vec3(posTileX, -1.5, posTileY)), m_pathModel(type){};
    ~Arc() = default;

    inline const glm::vec3 getPosition() const { return m_position; }
    inline void            setPosition(glm::vec3 pos) { m_position = pos; }

    void draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix);
};