#pragma once 

#include "glimac/Geometry.hpp"
#include <glm/glm.hpp>

class Camera {
public:
    Camera();

    void applique_rotation();
    void applique_translation();

    glm::vec3 position();
    float pan();

    //mouvement camera
    void avance_tout_droit();
    void avance_en_arriere();
    void avance_gauche();
    void avance_droite();
    void avance_haut();
    void avance_bas();
    void tourne_droite();
    void tourne_gauche();
    void tourne_haut();
    void tourne_bas();
    void hauteur_fixe(float h_sol, float h_cam);
    void reinitialise_position();

private:
    void translation(glm::vec3 direction);
    glm::vec3 forward();
    glm::vec3 right();
    glm::vec3 up();
	glm::vec3 _position;

    float _pan = 1.8f;
    float _tilt = 0.f;

    float _vitesse_deplacement = 1.f;
    float _vitesse_rotation = 0.02f;
};