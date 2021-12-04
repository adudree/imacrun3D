#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "common.hpp"

namespace glimac {

class Player 
{
    private:
        // nom
        // score 
        // position 
        // direction 
        // model 
        // texture 

        std::string m_nom; 
        int m_score;
        glm::vec3 m_position; 


    public: 
        Player() : m_nom("John Doe"), m_score(0), m_position(glm::vec3(0)) {}
        ~Player() = default;

        //draw() // chargement + affichage obj 3D 
        //inline void moveForward() { m_position[2] ++; }
        //inline void moveLeft() { m_position[0] --; }
        //inline void moveRight() { m_position[0] ++; }
        //inline void jump() { /* ici fonction LAMBDA pour sauter (mouvement parabolique) */ }
        //inline void squat() { /* ici  */ }
        //collision(Obstacle)
        //collision(Coin)
};

}