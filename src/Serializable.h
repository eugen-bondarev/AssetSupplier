#pragma once

#include "Common.h"

class Serializable
{
public:
	struct Info
	{
		size_t entrySize;
		size_t numEntries;

		size_t GetContentSize() const
		{
			return entrySize * numEntries;
		}

		size_t GetFullSizeInBytes() const
		{
			return sizeof(Info) + GetContentSize();
		}
	};

	struct Place
	{
		size_t size;
		size_t offset;
	};

	Serializable(const size_t sizeInBytes)
	{
		const Info info{ 1, sizeInBytes };
		Alloc(info.GetFullSizeInBytes());
		FillMem(&info, sizeof(Info));
	}

	Serializable(const Serializable& original, const size_t size = 0, const size_t offset = 0)
	{
		const Info info{ original.GetInfo() };
		const size_t sizeInBytes{ size == 0 ? info.GetFullSizeInBytes() : size };
		Alloc(sizeInBytes);
		FillMem(original.GetData(offset), sizeInBytes);
	}

	template <typename T>
	Serializable(const std::vector<T>& vector)
	{
		const Info info{ sizeof(T), vector.size() };
		Alloc(info.GetFullSizeInBytes());
		size_t offset{ 0 };
		FillMem(&info, sizeof(Info), &offset);
		FillMem(vector.data(), info.GetContentSize(), &offset);
	}

	Serializable(const std::vector<const Serializable*>& children)
	{
		size_t sizeInBytes{ 0 };
		for (size_t i = 0; i < children.size(); ++i)
		{
			const Serializable& child{ *children[i] };
			sizeInBytes += child.GetInfo().GetFullSizeInBytes();
		}
		Alloc(sizeInBytes);

		size_t offset{ 0 };
		for (size_t i = 0; i < children.size(); ++i)
		{
			const Serializable& child{ *children[i] };
			const Info info{ child.GetInfo() };
			const size_t childSizeInBytes{ info.GetFullSizeInBytes() };
			FillMem(child.GetData(0), childSizeInBytes, &offset);
		}
	}

	Place GetPlace(const size_t index)
	{
		Place currentPlace{ GetInfo(0).GetFullSizeInBytes(), 0 };
		for (size_t i = 0; i < index; ++i)
		{
			currentPlace.offset += currentPlace.size;
			currentPlace.size = GetInfo(currentPlace.offset).GetFullSizeInBytes();
		}
		return currentPlace;
	}

	Serializable Extract(const size_t index)
	{
		const Place place = GetPlace(index);
		Serializable serializable(place.size);
		serializable.FillMem(data + place.offset, place.size);
		return serializable;
	}

	~Serializable()
	{
		delete[] data;
	}

	Info GetInfo(const size_t offset = 0) const
	{
		return *reinterpret_cast<Info*>(data + offset);
	}

	template <typename T = char*>
	T GetData(const size_t offset = sizeof(size_t) * 2)
	{
		return reinterpret_cast<T>(data + offset);
	}

	template <typename T = char*>
	const T GetData(const size_t offset = sizeof(size_t) * 2) const
	{
		return reinterpret_cast<const T>(data + offset);
	}

	template <typename T>
	std::vector<T> ToVector() const
	{
		std::vector<T> result(GetInfo().numEntries);
		for (size_t i = 0; i < result.size(); ++i)
		{
			result[i] = GetData<T*>()[i];
		}
		return result;
	}

private:
	char* data;

	void Alloc(const size_t sizeInBytes)
	{
		data = new char[sizeInBytes];
	}

	void FillMem(const void* setData, const size_t size, size_t* offset = nullptr)
	{
		memcpy(data + (offset ? *offset : 0), setData, size);
		if (offset != nullptr)
		{
			*offset += size;
		}
	}
};

struct Car
{
	int ps;
	int year;
	float maxSpeed;
};