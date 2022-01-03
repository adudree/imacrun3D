#pragma once

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Map.hpp"
#include "Model.hpp"
#include "glimac/glm.hpp"

class Player {
private:
    std::string     m_nom      = "John Doe";
    int             m_score    = 0;
    glm::vec3       m_position = glm::vec3(0);
    float           m_speed;
    float           m_InitialY;
    float           m_InitialZ;
    Model           m_model;
    glimac::Program m_program = glimac::loadProgram("assets/shaders/Model.vs.glsl", "assets/shaders/Model.fs.glsl");

    char m_orientation = 'N';

    void moveForward();

public:
    bool m_isJumping       = false;
    bool m_isDown          = false;
    bool m_isFalling       = false;
    bool m_isMovingForward = false;

    Player()
        : m_model("assets/models/player/StarSparrow.obj") {}
    ~Player() = default;

    inline const glm::vec3 getPosition() const { return m_position; }
    inline char            getOrientation() const { return m_orientation; }
    inline int             getScore() const { return m_score; }

    inline void setPosition(const glm::vec3& pos) { m_position = pos; }
    inline void setSpeed(const float& speed) { m_speed = speed; }
    inline void setOrientation(const char& o) { m_orientation = o; }
    inline void setScore(const int& score) { m_score = score; }
    inline void addPointToScore(int point) { m_score += point; }

    void draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix); // chargement + affichage obj 3D

    void update();
    void moveLeft();
    void moveRight();
    void jump();
    void down();

    void verticalInitialize();

    void updateMovement();

    void fall();

    bool canMoveRight(float tilePosition);
    bool canMoveLeft(float tilePosition);
};