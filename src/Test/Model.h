//#include <assimp/postprocess.h>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//
//#include <stdexcept>
//#include <vector>
//
//#include "../Asset.h"
//
//struct Vec2 { float x{ 0 }, y{ 0 }; };
//struct Vec3 { float x{ 0 }, y{ 0 }, z{ 0 }; };
//
//struct Vertex
//{
//	Vec3 position;
//	Vec2 uv;
//	Vec3 normal;
//};
//
//struct Model
//{
//	std::vector<Vertex> vertices;
//	std::vector<uint32_t> indices;
//
//	Model(Asu::Asset& asset)
//	{
//        Assimp::Importer importer;
//
//        //const aiScene* scene = importer.ReadFile(filePath(), aiProcess_Triangulate | aiProcess_FlipUVs);
//        const aiScene* scene = importer.ReadFileFromMemory(asset.data.data(), asset.data.size(), aiProcess_Triangulate | aiProcess_FlipUVs);
//
//        if (!scene)
//        {
//            throw std::runtime_error("Failed to open model file.");
//        }
//
//        const size_t meshIndex{ 0 };
//
//        // for (size_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
//        {
//            const aiMesh* mesh{ scene->mMeshes[meshIndex] };
//            vertices.resize(mesh->mNumVertices);
//
//            for (size_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex)
//            {
//                const aiVector3D& position = mesh->mVertices[vertexIndex];
//                const aiVector2D& uv = { mesh->mTextureCoords[0][vertexIndex].x, mesh->mTextureCoords[0][vertexIndex].y };
//                const aiVector3D& normal = mesh->mNormals[vertexIndex];
//
//                memcpy(&vertices[vertexIndex].position, &position, sizeof(Vec3));
//                memcpy(&vertices[vertexIndex].uv, &uv, sizeof(Vec2));
//                memcpy(&vertices[vertexIndex].normal, &normal, sizeof(Vec3));
//            }
//
//            indices.resize(mesh->mNumFaces * 3);
//
//            const unsigned int indicesPerFace = 3;
//
//            for (int i = 0; i < mesh->mNumFaces; ++i)
//            {
//                for (int j = 0; j < indicesPerFace; ++j)
//                {
//                    indices[i * indicesPerFace + j] = mesh->mFaces[i].mIndices[j];
//                }
//            }
//        }
//	}
//};