#pragma once

#include "glimac/SDLWindowManager.hpp"
#include "glimac/Image.hpp"

#include <GL/glew.h>

void createTexture(GLuint &texture, std::unique_ptr<glimac::Image> &imagePointer);
