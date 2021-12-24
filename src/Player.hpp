#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "Hole.hpp"
#include "Map.hpp"
#include "Sphere.hpp"
#include "Tile.hpp"
#include "VAO.hpp"
#include "glimac/glm.hpp"

class Player {
private:
    std::string m_nom = "John Doe";
    int         m_score = 0;
    glm::vec3   m_position = glm::vec3(0);
    float       m_speed;

    // VBO<ShapeVertex> m_vbo;
    // VAO<ShapeVertex> m_vao;

    GLuint m_texture;

    std::vector<ShapeVertex> buildVertices();
    void                     buildVAO();

    void setTexture();

public:
    bool isJumping;
    bool isLowed;
    bool isFalling;
    bool isMovingForward;

    Player()
        // :  m_vbo(buildVertices()), m_vao()
        {
            // buildVAO();
        }

    ~Player() = default;

    inline const glm::vec3 getPosition() const { return m_position; }

    inline void setPosition(glm::vec3 pos)  {m_position = pos; }
    inline void setSpeed(float speed)      {m_speed = speed;}

    void draw(); // chargement + affichage obj 3D

    inline void moveForward()   {m_position.z += m_speed * 0.1;}
    inline void moveLeft()      {m_position.x -= m_speed * 0.1;}
    inline void moveRight()     {m_position.x += m_speed * 0.1;}
    void        jump();

    inline void fall()          {m_position.y += m_speed * 0.1;}       // TODO : axe y inversé !  


    //inline void squat() { /* height objet/2 */ } // GILET JAUNE 10 SQUATS 
    
    bool canMoveRight(float tilePosition, float tileWidth);
    bool canMoveLeft(float tilePosition, float tileWidth);

    //collision(Coin)

    void fallingTest();
};