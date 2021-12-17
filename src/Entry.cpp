#include "Entry.h"

#include <fstream>

namespace Asu
{
	Entry::Entry(const String& location, const size_t size, size_t& offset) : location{ location }, size{ size }
	{
		ASU_INFO("File: {0}, size: {1} b, offset: {2} b", location, size, offset);
		offset += size;
	}

	const String& Entry::GetLocation() const
	{
		return location;
	}

	String Entry::GetExtension() const
	{
		const size_t lastDot{ location.find_last_of(".") };
		const String extension{ location.substr(lastDot + 1, location.size() - lastDot) };
		return extension;
	}

	size_t Entry::GetSize() const
	{
		return size;
	}

	void SerializeEntryTable(const String& path, const EntryTable& entryTable)
	{
		std::ofstream file(path);

		for (size_t i = 0; i < entryTable.size(); ++i)
		{
			//file << entryTable[i].GetLocation() << ' ' << entryTable[i].GetSize() << '\n';
		}
	}
}