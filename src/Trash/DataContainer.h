#pragma once

#include <cstring>

struct DataContainer
{
	DataContainer(const size_t size, const void* source) : size{ size }
	{
		data = new char[size];
		memcpy(data, source, size);
	}

	DataContainer(const DataContainer& original) : size{ original.size }
	{
		data = new char[size];
		memcpy(data, original.data, size);
	}

	~DataContainer()
	{
		delete[] data;
	}

	size_t GetSize() const
	{
		return size;
	}

	char* data;
	size_t size;
};