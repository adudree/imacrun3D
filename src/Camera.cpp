/* 

Contrôle de la caméra

Le jeu doit contenir deux types de caméra :

— une caméra centrée sur l’explorateur, qui permet de tourner autour et de zoomer à l’aide de la
souris ;

— une caméra permettant de voir à travers les yeux de l’explorateur et offrant la possibilité de tourner
la tête à l’aide de la souris (attention, nous ne sommes pas dans l’Exorciste, les déplacements de
la tête doivent être limités).

À tout moment, le joueur peut changer de vue en appuyant sur la touche C et bloquer la caméra dans
une configuration idéale pour jouer avec la touche L.

*/

#include <cmath>
#include "Camera.hpp"

Camera::Camera()
{
	_position = glm::vec3(0, 65.f, 0);
}

void Camera::applique_rotation() {
    glm::mat4 VM = glm::mat4(1);
	glm::rotate(VM, glm::radians(-_tilt), glm::vec3(1.f, 0.f, 0.f));
	glm::rotate(VM, glm::radians(-_pan), glm::vec3(0.f, 1.f, 0.f));
}

void Camera::applique_translation() {
    glm::mat4 VM = glm::mat4(1);
	glm::translate(VM, glm::vec3(-_position.x, -_position.y, -_position.z));
}

glm::vec3 Camera::position() {
	return _position;
}

float Camera::pan() {
	return _pan;
}

// Fonctions privés

void Camera::translation(glm::vec3 direction) {
	_position += direction * _vitesse_deplacement;
}

glm::vec3 Camera::forward() {
	return glm::vec3(
		-sin(_pan),
		0,
		-cos(_pan)
	);
}

glm::vec3 Camera::right() {
	return glm::vec3(
		cos(_pan),
		0,
		-sin(_pan)
	);
}

glm::vec3 Camera::up() {
 	return glm::vec3(
		0,
		1,
		0
	);
}


// Fonctions mouvements caméra

void Camera::avance_tout_droit() {
	translation(forward());
}

void Camera::avance_en_arriere() {
	translation(-forward());
}

void Camera::avance_gauche() {
	translation(-right());
}

void Camera::avance_droite() {
	translation(right());
}

void Camera::avance_haut() {
	translation(up());
}

void Camera::avance_bas() {
	translation(-up());
}

void Camera::tourne_droite() {
	_pan -= _vitesse_rotation;
}

void Camera::tourne_gauche() {
	_pan += _vitesse_rotation;
}

void Camera::tourne_haut() {
	_tilt += _vitesse_rotation;
}

void Camera::tourne_bas() {
	_tilt -= _vitesse_rotation;
}

void Camera::hauteur_fixe(float h_sol, float h_cam){
	_position.y = h_cam + h_sol;
}

void Camera::reinitialise_position(){
	_position = glm::vec3(0, 65.f, 0);
}