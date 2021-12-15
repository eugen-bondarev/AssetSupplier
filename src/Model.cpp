#include "Model.h"

#include <stdexcept>

Model::Model(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene)
    {
        throw std::runtime_error("Failed to open model file " + path);
    }

    const size_t meshIndex{ 0 };

    // for (size_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
    {
        const aiMesh* mesh{ scene->mMeshes[meshIndex] };
        vertices.resize(mesh->mNumVertices);

        for (size_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex)
        {
            const aiVector3D& position = mesh->mVertices[vertexIndex];
            const aiVector2D& texCoords = { mesh->mTextureCoords[0][vertexIndex].x, mesh->mTextureCoords[0][vertexIndex].y };
            const aiVector3D& normal = mesh->mNormals[vertexIndex];

            memcpy(&vertices[vertexIndex].position, &position, sizeof(float) * 3);
            memcpy(&vertices[vertexIndex].texCoords, &texCoords, sizeof(float) * 2);
            memcpy(&vertices[vertexIndex].normal, &normal, sizeof(float) * 3);
        }

        indices.resize(static_cast<size_t>(mesh->mNumFaces) * 3);

        const size_t indicesPerFace = 3;

        for (size_t i = 0; i < mesh->mNumFaces; ++i)
        {
            for (size_t j = 0; j < indicesPerFace; ++j)
            {
                indices[i * indicesPerFace + j] = mesh->mFaces[i].mIndices[j];
            }
        }
    }
}