#pragma once

#include "common.hpp"
#include "SDLWindowManager.hpp"
#include "Image.hpp"

namespace glimac {

void createTexture(GLuint &texture, std::unique_ptr<Image> &imagePointer);
void createVAO(GLuint &vbo, GLuint &vao);
void gestionEvent(bool &done, SDLWindowManager &windowManager);

}