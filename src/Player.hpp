#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "Hole.hpp"
#include "Tile.hpp"
#include "glimac/glm.hpp"

class Player {
private:
    // model
    // texture

    std::string m_nom;
    int         m_score;
    glm::vec3   m_position;

    bool isJumping;
    bool isLowed;
    bool isMovingForward;

public:
    Player()
        : m_nom("John Doe"), m_score(0), m_position(glm::vec3(0.f)) {}
    ~Player() = default;

    inline const glm::vec3 getPosition() const { return m_position; }

    inline void setPosition(glm::vec3 pos) { m_position = pos; }

    //draw() // chargement + affichage obj 3D

    inline void moveForward() { m_position.z++; }
    void        moveSide(const float& indice);
    void        jump();

    //inline void squat() { /* height objet/2  */ }

    void collision(Hole& hole);

    //collision(Coin)

    bool isOnTile(Tile& tile);
    bool isFalling();
};
