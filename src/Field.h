#pragma once

#include <vector>

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
		_FillMem(original.entry, sizeInBytes, 0);
	}

	Field& operator=(const Field& original)
	{
		entry = new char[sizeInBytes];
		_FillMem(original.entry, sizeInBytes, 0);
		return (*this);
	}

	size_t GetSizeInBytes() const
	{
		return sizeInBytes;
	}

	template <typename T>
	T& InterpretAs(const size_t index = 0, const size_t offset = 0)
	{
		return _InterpretAs<T>(index, offset);
	}

	template <typename T>
	const T& InterpretAs(const size_t index = 0, const size_t offset = 0) const
	{
		return _InterpretAs<T>(index, offset);
	}

	void SetData(const std::vector<const Field*>& fields)
	{
		size_t offset{ 0 };
		for (size_t i = 0; i < fields.size(); ++i)
		{
			const size_t currentFieldSize{ fields[i]->GetSizeInBytes() };
			SetData(*fields[i], currentFieldSize, offset);
			offset += currentFieldSize;
		}
	}

	void SetData(const void* setData, const size_t size = 0, const size_t offset = 0)
	{
		_FillMem(setData, size == 0 ? sizeInBytes : size, offset);
	}

	void SetData(const Field& field, const size_t size = 0, const size_t offset = 0)
	{
		_FillMem(field.entry, size == 0 ? sizeInBytes : size, offset);
	}

	template <typename T>
	std::vector<T> ToVector(const size_t size, const size_t offset = 0)
	{
		std::vector<T> result(size);
		for (size_t i = 0; i < result.size(); ++i)
		{
			const T& item = InterpretAs<T>(i, offset);
			result[i] = item;
		}
		return result;
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

	template <typename T>
	T& _InterpretAs(const size_t index, const size_t offset)
	{
		return *(T*)(void*)(entry + offset + index * sizeof(T));
	}

	void _FillMem(const void* source, const size_t size, const size_t offset)
	{
		memcpy(entry + offset, source, size);
	}
};