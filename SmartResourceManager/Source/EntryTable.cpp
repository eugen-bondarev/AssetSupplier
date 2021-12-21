#include "EntryTable.h"

#include "Logging.h"
#include "Util.h"

#include <filesystem>
#include <algorithm>
#include <fstream>
#include <sstream>

namespace srm
{
	void EntryTable::CreateTableFile(const String& path)
	{
		std::ofstream outputStream{ path };

		for (size_t i = 0; i < entries.size(); i++)
		{
			outputStream << entries[i].GetLocation() << ' ' << entries[i].GetSize() << ' ' << entries[i].GetOffset();
			if (i != entries.size() - 1)
			{
				outputStream << '\n';
			}
		}
	}

	void EntryTable::CreateDataFile(const String& path, const String& pathPrefix)
	{
		std::ofstream outputStream{ path, std::ios::binary };

		/*
		* We need to sort the table by offset before creating a data file.
		* So either we need to create a copy and sort it or we 
		* can sort this EntryTable by offset, create the data file 
		* based on it, and then sort it in the alphabetical order.
		* Here I decide to create a copy and sort it once.
		*/
#ifndef SRM_DATA_FILE_SORT_TWICE
		EntryTable copy{ *this };
		copy.SortByOffset();
		const Vec<Entry>& preparedEntities{ copy.entries };
#else
		SortByOffset();
		const Vec<Entry>& preparedEntities{ entries };
#endif

		for (size_t i = 0; i < preparedEntities.size(); ++i)
		{
			const String currentFileFullPath{ pathPrefix + "/" + preparedEntities[i].GetLocation() };
			std::ifstream currentFile{ currentFileFullPath, std::ios::binary };
			outputStream << currentFile.rdbuf();
		}

#ifdef SRM_DATA_FILE_SORT_TWICE
		SortAlphabetically();
#endif
	}

	static void LineToEntry(Entry& entry, const String& line)
	{
		std::istringstream stringStream{ line };

		String name{ "" };
		size_t size{ 0 };
		size_t offset{ 0 };

		stringStream >> name >> size >> offset;

		entry.SetLocation(name);
		entry.SetSize(size);
		entry.SetOffset(offset);
	}

	static void AppendToEntryTable(
		EntryTable& entryTable,
		const String& root,
		const String& pathWithMessySlashes,
		size_t& offset,
		const Vec<String>& ignoreFiles
	)
	{
		const String fullPath{ Util::ReplaceAll(pathWithMessySlashes, "\\", "/") };
		const String localPath{ fullPath.substr(root.size() + 1, fullPath.size() - root.size()) };
		const size_t size{ Util::GetFileSize(fullPath) };

		const Entry entry{ localPath, size, offset };

		const bool entryIgnored{ std::find(std::begin(ignoreFiles), std::end(ignoreFiles), entry.GetLocation()) != std::end(ignoreFiles) };

		if (entry.GetSize() != 0 && !entryIgnored)
		{
			entryTable.entries.push_back(entry);
			offset += size;
		}
		else
		{
			SRM_CONSOLE_WARN("Skipping file: %s", localPath.c_str());
		}
	}

	void EntryTable::Load(const String& path)
	{
		std::ifstream inputStream{ path };
		String line;

		entries.clear();

		while (std::getline(inputStream, line))
		{
			Entry entry;
			LineToEntry(entry, line);
			entries.push_back(entry);
		}
	}

	void EntryTable::Create(const String& root, const Vec<String>& ignoreFiles)
	{
		SRM_CONSOLE_INFO("Creating entry table: %s", root.c_str());

		size_t offset{ 0 };

		entries.clear();

		for (const auto& entry : std::filesystem::recursive_directory_iterator(root))
		{
			if (!entry.is_directory())
			{
				AppendToEntryTable(*this, root, entry.path().string(), offset, ignoreFiles);
			}
		}

		// Now it's required to sort, since we want
		// to perform binary search later on.
		SortAlphabetically();
	}

	void EntryTable::SortAlphabetically()
	{
		std::sort(
			std::begin(entries),
			std::end(entries),
			[&](const Entry& a, const Entry& b)
			{
				return a.GetLocation() < b.GetLocation();
			}
		);
	}

	void EntryTable::SortByOffset()
	{
		std::sort(
			std::begin(entries),
			std::end(entries),
			[](const Entry& a, const Entry& b)
			{
				return a.GetOffset() < b.GetOffset();
			}
		);
	}
}