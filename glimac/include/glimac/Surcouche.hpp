#pragma once

#include "common.hpp"
#include "SDLWindowManager.hpp"
#include "Image.hpp"
#include "Program.hpp"
#include "glimac/common.hpp"
#include <iostream>

namespace glimac {

void createTexture(GLuint &texture, std::unique_ptr<Image> &imagePointer);
void createVAO(GLuint &vbo, GLuint &vao);
void createVAO(GLuint &vbo, GLuint &vao, GLuint &ibo);

void gestionEvent(bool &done, SDLWindowManager &windowManager);
void loadShader(Program &program, int &argc, char** &argv);

}