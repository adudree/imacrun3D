#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "Hole.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "glimac/glm.hpp"
#include "Sphere.hpp"
#include "IBO.hpp"
#include "VAO.hpp"
#include "VBO.hpp"

class Player {
private:
    // model
    // texture

    std::string m_nom;
    int         m_score;
    glm::vec3   m_position;
    float       m_speed = 0.5;

    bool isJumping;
    bool isLowed;
    bool isMovingForward;

    Sphere m_sphere; 
    
    VBO<ShapeVertex> m_vbo;
    VAO<ShapeVertex> m_vao;

    GLuint m_texture;

    std::vector<ShapeVertex> buildVertices();
    void             buildVAO();

    void setTexture();

public:

    Player(GLuint texture)
        : m_nom("John Doe"), m_score(0), m_position(glm::vec3(0.f)), 
          m_sphere(Sphere(m_position, 1, 32, 16)),      // pour l'instant ; sera obj 3D plus tard
          m_vbo(buildVertices()), m_vao(), 
          m_texture(texture) {
            buildVAO();
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
    
    glm::vec2 getActiveTile(float tileWidth, float  tileLength);
    char tileDetection(glm::vec2 coordActiveTile);
    void tilesConditions(char &tile);

    //collision(Coin)

    bool isFalling();
};