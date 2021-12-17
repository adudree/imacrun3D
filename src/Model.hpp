#pragma once
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <stb/stb_image.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "Mesh.hpp"

class Model 
{
    public:
        Model(std::string path)
        {
            loadModel(path);
        }
        void Draw(glimac::Program& program);
    private:
        std::vector<Mesh> m_meshes; 
        std::string m_directory; 
        std::vector<TextureMesh> m_texturesLoaded;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<TextureMesh> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

