#include "DataContainer.h"
#include "Common.h"
#include "Field.h"

struct Vec2 { float x{ 0.0f }, y{ 0.0f }; };
struct Vec3 { float x{ 0.0f }, y{ 0.0f }, z{ 0.0f }; };

struct Vertex3D
{
	Vec3 position{0.0f, 1.0f, 2.0f};
	Vec2 uv{ 3.0f, 4.0f };
	Vec3 normal{ 5.0f, 6.0f, 7.0f };
};

int main()
{
	std::vector<Vertex3D> vertices(10);
	std::vector<uint32_t> indices(10);

	for (size_t i = 0; i < indices.size(); ++i)
	{
		indices[i] = i;
	}

	Field verticesField(sizeof(Vertex3D) * 10);
	Field indicesField(sizeof(uint32_t) * 10);
	verticesField.SetData(vertices.data());
	indicesField.SetData(indices.data());

	Field asset(verticesField.GetSizeInBytes() + indicesField.GetSizeInBytes());

	asset.SetData({
		&verticesField,
		&indicesField,
	});

	std::vector<Vertex3D> verticesVector = asset.ToVector<Vertex3D>(10);
	for (size_t i = 0; i < 10; ++i)
	{
		Vertex3D& vertex = verticesVector[i];
		std::cout << vertex.position.x << ' ' << vertex.position.y << ' ' << vertex.position.z << '\n';
		std::cout << vertex.uv.x << ' ' << vertex.uv.y << '\n';
		std::cout << vertex.normal.x << ' ' << vertex.normal.y << ' ' << vertex.normal.z << '\n';
	}

	std::vector<uint32_t> indicesVector = asset.ToVector<uint32_t>(10, 10 * sizeof(Vertex3D));
	for (size_t i = 0; i < 10; ++i)
	{
		std::cout << indicesVector[i] << '\n';
	}
}