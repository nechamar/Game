#pragma once
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <boost/log/trivial.hpp>

#include "GL/glew.h"
#include "glm/glm.hpp"

#include <cstdint>
#include <vector>



struct Mesh {
    uint32_t number_of_triangles;
    GLuint EBO;
    GLuint VBO;
    GLuint VAO;
    uint32_t material_index;
};

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emission;
    float shininess;

    bool useEmissionTexture;
    GLuint emissionTexture;
    bool useAmbientTexture;
    GLuint ambientTexture;
    bool useDiffuseTexture;
    GLuint diffuseTexture;
};

struct Model
{
    std::vector<Mesh> meshes;
    std::vector<Material> materials;
};

Model* load_mesh(std::string& filename);