#pragma once

#include "Common.h"
#include "Asset.h"

namespace Asu
{
	class Entry
	{
	public:
		Entry(const std::string& location, const size_t size, const size_t offset);

		const String& GetLocation() const;
		String GetExtension() const;
		size_t GetSize() const;
		size_t GetOffset() const;

	private:
		String location;
		size_t size;
		size_t offset;
	};

	using EntryTable = Vec<Entry>;

	void SerializeEntryTable(const String& path, const EntryTable& entryTable);
	void Archive(const String& path, const String& pathPrefix, const EntryTable& entryTable);

	void LoadAsset(Asset& asset, const String& archivePath, const Entry& entry);
}