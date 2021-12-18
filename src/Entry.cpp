#include "Entry.h"

#include <fstream>

namespace Asu
{
	Entry::Entry(const std::string& location, const size_t size, const size_t offset) : location{ location }, size{ size }, offset{ offset }
	{
		ASU_INFO("File: {0}, size: {1} b, offset: {2} b", location, size, offset);
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

	size_t Entry::GetOffset() const
	{
		return offset;
	}

	void SerializeEntryTable(const String& path, const EntryTable& entryTable)
	{
		std::ofstream file(path);

		for (size_t i = 0; i < entryTable.size(); i++)
		{
			file << entryTable[i].GetLocation() << ' ' << entryTable[i].GetSize() << ' ' << entryTable[i].GetOffset() << '\n';
		}
	}

	void Archive(const String& path, const String& pathPrefix, const EntryTable& entryTable)
	{
		std::ofstream output{ path, std::ios::binary };

		for (size_t i = 0; i < entryTable.size(); ++i)
		{
			const String currentFileFullPath{ pathPrefix + "/" + entryTable[i].GetLocation() };
			std::ifstream currentFile{ currentFileFullPath, std::ios::binary };
			output << currentFile.rdbuf();
		}
	}

	void LoadAsset(Asset& asset, const String& archivePath, const Entry& entry)
	{
		asset.data.resize(entry.GetSize());

		std::ifstream dataStream{ archivePath, std::ios::binary };
		//dataStream.seekg(entry.GetOffset());
		dataStream.seekg(entry.GetOffset());
		//dataStream.read(asset.data.data(), entry.GetSize());
		dataStream.read(asset.data.data(), entry.GetSize());
	}
}