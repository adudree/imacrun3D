#include "Arc.hpp"

void Arc::draw(const glm::mat4& projMatrix, const glm::mat4& mvMatrix)
{
    GLint locMVPMatrix    = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix");
    GLint locMVMatrix     = glGetUniformLocation(m_program.getGLId(), "uMVMatrix");
    GLint locNormalMatrix = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix");
    GLint locModelMatrix  = glGetUniformLocation(m_program.getGLId(), "uModel");
    GLint locTexture      = glGetUniformLocation(m_program.getGLId(), "texture_diffuse1");

    glm::mat4 ProjMatrix = projMatrix;
    glm::mat4 MVMatrix   = mvMatrix;

    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 modMatrix    = glm::translate(glm::mat4(1), m_position) *
                          glm::rotate(glm::mat4(1.), glm::radians(130.0f), glm::vec3(m_randomRotateX, m_randomRotateY, m_randomRotateZ)) *
                          glm::scale(glm::mat4(1.), glm::vec3(m_randomModifierScale));

    m_program.use();
    glUniformMatrix4fv(locModelMatrix, 1, GL_FALSE, glm::value_ptr(modMatrix));
    glUniformMatrix4fv(locMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(locMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(locNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniform1i(locTexture, 0);
    m_model.Draw(m_program);
}