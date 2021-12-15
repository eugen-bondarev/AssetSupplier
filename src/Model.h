#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

struct Vec2 { float x{ 0 }, y{ 0 }; };
struct Vec3 { float x{ 0 }, y{ 0 }, z{ 0 }; };

struct Vertex3D
{
    Vec3 position;
    Vec2 texCoords;
    Vec3 normal;
};

struct Model
{
    std::vector<Vertex3D> vertices;
    std::vector<uint32_t> indices;

    Model(const std::string& path);
};