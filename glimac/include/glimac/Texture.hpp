#pragma once

#include <iostream>

#include "common.hpp"
#include "SDLWindowManager.hpp"
#include "Image.hpp"
#include "Program.hpp"

namespace glimac {

void createTexture(GLuint &texture, std::unique_ptr<Image> &imagePointer);
}