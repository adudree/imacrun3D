#pragma once

#include <GL/glew.h>
#include "glimac/Image.hpp"
#include "glimac/SDLWindowManager.hpp"

void createTexture(GLuint& texture, std::unique_ptr<glimac::Image>& imagePointer);
