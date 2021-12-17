#pragma once

#include "Common.h"

template <typename T>
class Array
{
public:
	Array() : size{ 0 }, data{ nullptr }
	{

	}

	Array(const size_t size) : size{ size }
	{
		data = new T[size];
	}

	Array(const size_t size, const void* setData) : size{ size }
	{
		data = new T[size];
		memcpy(data, setData, size);
	}

	Array(const char* string) : size{ strlen(string) }
	{
		data = new T[size];
		memcpy(data, string, size);
	}

	template <typename T1>
	Array(const std::vector<T1>& vector) : size{ sizeof(T1) * vector.size() }
	{
		data = new T[size];
		memcpy(data, vector.data(), size);
	}

	Array(const Array& original) : Array{ original.size }
	{
		memcpy(data, original.data, size);
	}

	~Array()
	{
		if (IsDefined())
		{
			delete[] data;
		}
	}

	T& operator[](const size_t i)
	{
		ASSERT(i < size);
		return data[i];
	}

	const T& operator[](const size_t i) const
	{
		ASSERT(i < size);
		return (*this)[i];
	}

	size_t GetSize() const
	{
		return size;
	}

	template <typename T1>
	void operator=(const std::vector<T1>& vector)
	{
		size = sizeof(T1) * vector.size();
		data = new T[size];
		memcpy(data, vector.data(), size);
	}

	void operator=(const char* string)
	{
		size = strlen(string);
		data = new T[size];
		memcpy(data, string, size);
	}

	bool IsDefined() const
	{
		return size != 0 && data != nullptr;
	}

	operator bool() const
	{
		return IsDefined();
	}

private:
	size_t size;
	T* data;
};