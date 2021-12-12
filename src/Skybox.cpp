#include "Skybox.hpp"
#include <glimac/Program.hpp>
#include <iostream>
#include "GL/glew.h"
#include "glimac/Image.hpp"

unsigned int Skybox::loadCubemap(const std::array<const char*, 6>& texturesPaths)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (unsigned int i = 0; i < texturesPaths.size(); i++) {
        const auto image = glimac::loadImage(texturesPaths[i]);
        if (image) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
        }
        else {
            std::cout << "Cubemap tex failed to load at path: " << texturesPaths[i] << std::endl;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void Skybox::render(const glm::mat4& projMatrix, const glm::mat4& mvMatrix)
{
    glClearColor(1., 0., 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    m_skyboxProgram.use();
    GLint locprojection = glGetUniformLocation(m_skyboxProgram.getGLId(), "projection");
    GLint locview       = glGetUniformLocation(m_skyboxProgram.getGLId(), "view");
    glUniformMatrix4fv(locprojection, 1, GL_FALSE, glm::value_ptr(projMatrix));
    glUniformMatrix4fv(locview, 1, GL_FALSE, glm::value_ptr(mvMatrix));
    glBindVertexArray(*m_skyboxVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
}

Skybox::Skybox()
    : m_skyboxVBO{std::vector<SkyboxVertex>{
          {{-1.0f, 1.0f, -1.0f}},
          {{-1.0f, -1.0f, -1.0f}},
          {{1.0f, -1.0f, -1.0f}},
          {{1.0f, -1.0f, -1.0f}},
          {{1.0f, 1.0f, -1.0f}},
          {{-1.0f, 1.0f, -1.0f}},

          {{-1.0f, -1.0f, 1.0f}},
          {{-1.0f, -1.0f, -1.0f}},
          {{-1.0f, 1.0f, -1.0f}},
          {{-1.0f, 1.0f, -1.0f}},
          {{-1.0f, 1.0f, 1.0f}},
          {{-1.0f, -1.0f, 1.0f}},

          {{1.0f, -1.0f, -1.0f}},
          {{1.0f, -1.0f, 1.0f}},
          {{1.0f, 1.0f, 1.0f}},
          {{1.0f, 1.0f, 1.0f}},
          {{1.0f, 1.0f, -1.0f}},
          {{1.0f, -1.0f, -1.0f}},

          {{-1.0f, -1.0f, 1.0f}},
          {{-1.0f, 1.0f, 1.0f}},
          {{1.0f, 1.0f, 1.0f}},
          {{1.0f, 1.0f, 1.0f}},
          {{1.0f, -1.0f, 1.0f}},
          {{-1.0f, -1.0f, 1.0f}},

          {{-1.0f, 1.0f, -1.0f}},
          {{1.0f, 1.0f, -1.0f}},
          {{1.0f, 1.0f, 1.0f}},
          {{1.0f, 1.0f, 1.0f}},
          {{-1.0f, 1.0f, 1.0f}},
          {{-1.0f, 1.0f, -1.0f}},

          {{-1.0f, -1.0f, -1.0f}},
          {{-1.0f, -1.0f, 1.0f}},
          {{1.0f, -1.0f, -1.0f}},
          {{1.0f, -1.0f, -1.0f}},
          {{-1.0f, -1.0f, 1.0f}},
          {{1.0f, -1.0f, 1.0f}}}}
{
    glBindVertexArray(*m_skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, *m_skyboxVBO);

    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
