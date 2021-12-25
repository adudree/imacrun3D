#include "Sphere.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include "ShapeVertex.hpp"

void Sphere::build(GLfloat r, GLsizei discLat, GLsizei discLong)
{
    GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
    GLfloat dPhi = 2 * glm::pi<float>() * rcpLat, dTheta = glm::pi<float>() * rcpLong;

    //std::vector<ShapeVertex> data;

    // Construit l'ensemble des vertex
    for (GLsizei j = 0; j <= discLong; ++j) {
        GLfloat cosTheta = cos(-glm::pi<float>() / 2 + j * dTheta);
        GLfloat sinTheta = sin(-glm::pi<float>() / 2 + j * dTheta);

        for (GLsizei i = 0; i <= discLat; ++i) {
            ShapeVertex vertex;

            vertex.texCoords.x = i * rcpLat;
            vertex.texCoords.y = 1.f - j * rcpLong;

            vertex.normal.x = sin(i * dPhi) * cosTheta;
            vertex.normal.y = sinTheta;
            vertex.normal.z = cos(i * dPhi) * cosTheta;

            vertex.position = m_position + r * vertex.normal;

            m_data.push_back(vertex);
        }
    }

    m_nVertexCount = discLat * discLong * 6;

    // Construit les vertex finaux en regroupant les données en triangles:
    // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
    // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
    // avec i sur la bande correspondant à la longitude
    for (GLsizei j = 0; j < discLong; ++j) {
        GLsizei offset = j * (discLat + 1);
        for (GLsizei i = 0; i < discLat; ++i) {
            m_Vertices.push_back(m_data[offset + i]);
            m_Vertices.push_back(m_data[offset + (i + 1)]);
            m_Vertices.push_back(m_data[offset + discLat + 1 + (i + 1)]);
            m_Vertices.push_back(m_data[offset + i]);
            m_Vertices.push_back(m_data[offset + discLat + 1 + (i + 1)]);
            m_Vertices.push_back(m_data[offset + i + discLat + 1]);
        }
    }
}
