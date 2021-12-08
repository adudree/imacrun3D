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
        // isJumping        // test si est en train de sauter 
        // isLowed          // test si est baissé 
        // isMovingForward  // test si peut avancer
        // model 
        // texture 

        std::string m_nom; 
        int m_score;
        glm::vec3 m_position; 


    public: 
        Player() : m_nom("John Doe"), m_score(0), m_position(glm::vec3(0)) {}
        ~Player() = default;

        inline const glm::vec3 getPosition() const {return m_position;}

        inline void setPosition(glm::vec3 pos) { m_position = pos;}
        //draw() // chargement + affichage obj 3D 

        //inline void moveForward() { m_position[2] ++; }

        //inline void moveSide() { tant qu'on est sur la portion passageOk de la case, 
        // m_position[0] ++ ou --; (valeur <0 si décale à gauche) }


        //inline void jump() { /* ici fonction LAMBDA pour sauter (mouvement parabolique) : le saut doit être + long que la tuile */ }

        //inline void squat() { /* ici  */ }

        //collision(Obstacle)

        //collision(Coin)
};

}