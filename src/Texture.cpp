#include "Texture.hpp"

void createTexture(GLuint& texture, std::unique_ptr<glimac::Image>& imagePointer)
{
    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 imagePointer->getWidth(),
                 imagePointer->getHeight(),
                 0,
                 GL_RGBA,
                 GL_FLOAT,
                 imagePointer->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}