#pragma once

#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

struct Vertex {
    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec2 m_texCoords;
};

struct TextureMesh {
    unsigned int m_id;
    std::string  m_type;
    std::string  m_path;
};

class Mesh {
public:
    // Mesh data
    std::vector<Vertex>       m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<TextureMesh>  m_textures;

    Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, const std::vector<TextureMesh> textures);
    void Draw(glimac::Program& program);

private:
    unsigned int m_VAO, m_VBO, m_EBO; /*!< buffers needed to draw */
    void         setupMesh();
};
