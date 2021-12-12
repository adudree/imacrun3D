#include "skybox.hpp"
#include "GL/glew.h"

Skybox::Skybox()
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}
