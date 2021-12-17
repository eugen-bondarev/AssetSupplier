#pragma once

#include "Common.h"

namespace Asu
{
	class Entry
	{
	public:
		Entry(const String& location, const size_t size, size_t& offset);

		const String& GetLocation() const;
		String GetExtension() const;
		size_t GetSize() const;

	private:
		String location;
		size_t size;
		//size_t offset;
	};

	using EntryTable = Vec<Entry>;

	void SerializeEntryTable(const String& path, const EntryTable& entryTable);
}