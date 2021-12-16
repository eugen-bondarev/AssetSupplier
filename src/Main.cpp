#include "Common.h"

class Serializable
{
public:
	Serializable(const size_t sizeInBytes)
	{
		data = new char[sizeInBytes];
	}

	template <typename T>
	Serializable(const std::vector<T>& vector)
	{
		const size_t entrySize{ sizeof(T) };
		const size_t numEntries{ vector.size() };
		const size_t contentSize{ entrySize * numEntries };
		const size_t sizeInBytes{ sizeof(entrySize) + sizeof(numEntries) + contentSize };

		data = new char[sizeInBytes];
		size_t offset{ 0 };

		memcpy(data + offset, &entrySize, sizeof(entrySize)); offset += sizeof(entrySize);
		memcpy(data + offset, &numEntries, sizeof(numEntries)); offset += sizeof(numEntries);
		memcpy(data + offset, vector.data(), contentSize);
	}

	size_t GetEntrySize() const
	{
		const size_t offset{ 0 };
		return *reinterpret_cast<size_t*>(data + offset);
	}

	size_t GetNumEntries() const
	{
		const size_t offset{ sizeof(size_t) };
		return *reinterpret_cast<size_t*>(data + offset);
	}

	template <typename T = char*>
	T GetData()
	{
		return _GetData<T>();
	}

	template <typename T = char*>
	const T GetData() const
	{
		return _GetData<T>();
	}

	~Serializable()
	{
		delete[] data;
	}

private:
	template <typename T>
	T _GetData()
	{
		const size_t offset{ sizeof(size_t) * 2 };
		return reinterpret_cast<T>(data + offset);
	}
	
	char* data;
};

int main()
{
	std::vector<uint32_t> vector = {1, 2, 3, 4, 5, 6};
	Serializable serializable(vector);

	for (size_t i = 0; i < serializable.GetNumEntries(); ++i)
	{
		uint32_t& num = serializable.GetData<uint32_t*>()[i];
		VAR_OUT(num);
	}
}