#include "Loader.h"
#include <vector>
#include "GL/glew.h"
#include <cstdint>

void setup_mesh(std::vector<float>& vertices, std::vector<uint32_t> indices, GLuint& VAO, GLuint& VBO, GLuint& EBO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    constexpr uint32_t vertex_size = 8 * sizeof(float);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)(3 * sizeof(float)));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)(6 * sizeof(float)));

    glBindVertexArray(0);
}

Model* load_mesh(std::string& filename)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

    if (!scene)
    {
        BOOST_LOG_TRIVIAL(error) << "Error when reading mesh " << filename.c_str() << " " << importer.GetErrorString();
        return nullptr;
    }

    Model* model = new Model;

    model->meshes.resize(scene->mNumMeshes);

    for (size_t mesh_index = 0; mesh_index < scene->mNumMeshes; mesh_index++)
    {
        aiMesh* mesh = scene->mMeshes[mesh_index];
        std::vector<float> vertices(8 * mesh->mNumVertices);
        for (size_t vertex_index = 0; vertex_index < mesh->mNumVertices; vertex_index++)
        {
            // positions
            vertices[8 * (vertex_index) + 0] = mesh->mVertices[vertex_index].x;
            vertices[8 * (vertex_index) + 1] = mesh->mVertices[vertex_index].y;
            vertices[8 * (vertex_index) + 2] = mesh->mVertices[vertex_index].z;
            // normals                
            vertices[8 * (vertex_index) + 3] = mesh->mNormals[vertex_index].x;
            vertices[8 * (vertex_index) + 4] = mesh->mNormals[vertex_index].y;
            vertices[8 * (vertex_index) + 5] = mesh->mNormals[vertex_index].z;
            // tex coords
            vertices[8 * (vertex_index) + 6] = mesh->mTextureCoords[0][vertex_index].x;
            vertices[8 * (vertex_index) + 7] = mesh->mTextureCoords[0][vertex_index].y;
        }

        std::vector<uint32_t> indices(3 * mesh->mNumFaces);

        for (size_t i = 0; i < mesh->mNumFaces; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                indices[3 * i + j] = mesh->mFaces[i].mIndices[j];
            }
        }

        model->meshes[mesh_index].number_of_triangles = mesh->mNumFaces;

        setup_mesh(vertices, indices, model->meshes[mesh_index].VAO, model->meshes[mesh_index].VBO, model->meshes[mesh_index].EBO);

    }



    return model;
}
