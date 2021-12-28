#pragma once

#include <iostream>
#include <glimac/glm.hpp>
#include <vector>
#include "Map.hpp"
#include "Model.hpp"


class Coin {
private:
    int       m_point;
    glm::vec3 m_position = glm::vec3(0);

    // Model           m_model;
    glimac::Program m_program = glimac::loadProgram("assets/shaders/Model.vs.glsl", "assets/shaders/Model.fs.glsl");

public:
    explicit Coin(const glm::vec3 &pos)
        : m_point(1), m_position(pos) 
        //m_model("assets/models/coin/asteroid_2.obj")
    {}

    Coin(const Coin&)   = default;
    ~Coin()             = default;

    Coin& operator=(const Coin&) = default;

    inline glm::vec3 getPosition() const { return m_position; }

    void draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix);

    bool isCollision(const glm::vec3 &posPlayer) const;

    inline int getNbPoint() const {return m_point;}
};

void createCoins(Map &map, std::vector<std::unique_ptr<Coin>>& coins);
void updateCoins(const glm::vec3 &pos, std::vector<std::unique_ptr<Coin>>& coins);