#include "DataContainer.h"
#include "Common.h"

class Field
{
public:
	Field() = default;

	Field(const size_t sizeInBytes) : sizeInBytes{ sizeInBytes }
	{
		entry = new char[sizeInBytes];
	}

	Field(const Field& original) : sizeInBytes{ original.sizeInBytes }
	{
		entry = new char[sizeInBytes];
		memcpy(entry, original.entry, sizeInBytes);
	}

	void __Set(const std::vector<const Field*>& fields)
	{
		size_t offset{ 0 };
		for (size_t i = 0; i < fields.size(); ++i)
		{
			SetData(*fields[i], fields[i]->GetSizeInBytes(), offset);
			offset += fields[i]->GetSizeInBytes();
		}
	}

	void _Set(size_t& offset, const Field& field)
	{
		SetData(field, field.GetSizeInBytes(), offset);
		offset += field.GetSizeInBytes();
	}

	template <typename First, typename Second, typename... Rest>
	void _Set(size_t& offset, First&& first, Second&& second, Rest&&... rest)
	{
		_Set(offset, std::forward<First>(first));
		_Set(offset, std::forward<Second>(second), std::forward<Rest>(rest)...);
	}

	template <typename... Params>
	void Set(Params&&... params)
	{
		size_t offset{ 0 };
		_Set(offset, std::forward<Params>(params)...);
	}

	Field& operator=(const Field& original)
	{
		entry = new char[sizeInBytes];
		memcpy(entry, original.entry, sizeInBytes);
		return (*this);
	}

	size_t GetSizeInBytes() const
	{
		return sizeInBytes;
	}

	template <typename T>
	T& InterpretAs(const size_t index = 0, const size_t offset = 0)
	{
		return *(T*)(void*)(entry + offset + index * sizeof(T));
	}

	void SetData(const void* setData, const size_t size = 0, const size_t offset = 0)
	{
		memcpy(
			entry + offset,
			setData,
			size == 0 ? sizeInBytes : size
		);
	}

	void SetData(const Field& field, const size_t size = 0, const size_t offset = 0)
	{
		memcpy(
			entry + offset,
			field.entry,
			size == 0 ? sizeInBytes : size
		);
	}

	void Release()
	{
		delete[] entry;
		entry = nullptr;
		sizeInBytes = 0;
	}

	~Field()
	{
		if (IsDefined())
		{
			Release();
		}
	}

	bool IsDefined() const
	{
		return sizeInBytes != 0 && entry != nullptr;
	}

	operator bool() const
	{
		return IsDefined();
	}

private:
	char* entry{ nullptr };
	size_t sizeInBytes{ 0 };
};

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

	asset.__Set({
		&verticesField,
		&indicesField,
	});
	//asset.Set(
	//	verticesField,
	//	indicesField
	//);

	for (size_t i = 0; i < 10; ++i)
	{
		Vertex3D& vertex = asset.InterpretAs<Vertex3D>(i);
		std::cout << vertex.position.x << ' ' << vertex.position.y << ' ' << vertex.position.z << '\n';
		std::cout << vertex.uv.x << ' ' << vertex.uv.y << '\n';
		std::cout << vertex.normal.x << ' ' << vertex.normal.y << ' ' << vertex.normal.z << '\n';
	}

	for (size_t i = 0; i < 10; ++i)
	{
		uint32_t& index = asset.InterpretAs<uint32_t>(i, 10 * sizeof(Vertex3D));
		std::cout << index << '\n';
	}
}