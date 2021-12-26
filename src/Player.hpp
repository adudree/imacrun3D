#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
/* #include "IBO.hpp"
#include "Sphere.hpp"
#include "VAO.hpp"
#include "VBO.hpp" */
#include "glimac/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Model.hpp"

class Player {
private:
    std::string     m_nom      = "John Doe";
    int             m_score    = 0;
    glm::vec3       m_position = glm::vec3(0);
    float           m_speed;
    float           m_jumpInitialZ;
    Model           m_model;
    glimac::Program m_program = glimac::loadProgram("assets/shaders/Model.vs.glsl", "assets/shaders/Model.fs.glsl");

/*      GLuint m_texture;

        std::vector<ShapeVertex> buildVertices();
        void                     buildVAO();

    void setTexture(); */

    inline void moveForward() { m_position.z += m_speed * 0.1; }
    void        updateJump();

public:
    bool isJumping = false;
    bool isLowed;
    bool isFalling = false;
    bool isMovingForward;

    Player() 
        : m_model("assets/models/test2/StarSparrow.obj")
    {}
    // // :  m_vbo(buildVertices()), m_vao()
    // {
    //     // buildVAO();
    // }

    ~Player() = default;

    inline const glm::vec3 getPosition() const { return m_position; }

    inline void setPosition(glm::vec3 pos) { m_position = pos; }
    inline void setSpeed(float speed) { m_speed = speed; }

    void draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix); // chargement + affichage obj 3D

    void        update();
    inline void moveLeft() { m_position.x -= m_speed * 0.1; }
    inline void moveRight() { m_position.x += m_speed * 0.1; }
    void        jump();

    inline void fall() { m_position.y += m_speed * 0.1; } // TODO : axe y inversé !

    // inline void squat() { /* height objet/2 */ } // GILET JAUNE 10 SQUATS

    bool canMoveRight(float tilePosition, float tileWidth);
    bool canMoveLeft(float tilePosition, float tileWidth);

    // collision(Coin)

    void fallingTest();
};