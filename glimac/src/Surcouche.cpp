#include "glimac/common.hpp"
#include "glimac/Surcouche.hpp"
#include <iostream>

namespace glimac {

void createTexture(GLuint &texture, std::unique_ptr<Image> &imagePointer)
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
                imagePointer->getPixels()
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void createVAO(GLuint &vbo, GLuint &vao) 
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEX_COORD = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORD);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), 0);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glVertexAttribPointer(VERTEX_ATTR_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*) (6 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void gestionEvent(bool &done, SDLWindowManager &windowManager) 
{
    SDL_Event e;
    while(windowManager.pollEvent(e)) {
        if (e.type == SDL_QUIT) {
            done = true;
        }
    }

}

}