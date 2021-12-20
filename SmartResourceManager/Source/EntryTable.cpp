#include "EntryTable.h"

#include "Logging.h"
#include "Util.h"

#include <filesystem>
#include <algorithm>
#include <fstream>
#include <sstream>

namespace srm
{
	void EntryTable::Sort()
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

	void EntryTable::ToFile(const String& path)
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

	void LoadEntryList(EntryTable& table, const String& path)
	{
		std::ifstream inputStream{ path };
		String line;

		table.entries.clear();

		while (std::getline(inputStream, line))
		{
			Entry entry;
			LineToEntry(entry, line);
			table.entries.push_back(entry);
		}
	}

	static void AppendToEntryTable(
		EntryTable& table,
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
			table.GetEntries().push_back(entry);
			offset += size;
		}
		else
		{
			SRM_CONSOLE_WARN("Skipping file: %s", localPath.c_str());
		}
	}

	void CreateEntryList(EntryTable& table, const String& root, const Vec<String>& ignoreFiles)
	{
		SRM_CONSOLE_INFO("Creating entry table: %s", root.c_str());

		size_t offset{ 0 };

		table.entries.clear();

		for (const auto& entry : std::filesystem::recursive_directory_iterator(root))
		{
			if (!entry.is_directory())
			{
				AppendToEntryTable(table, root, entry.path().string(), offset, ignoreFiles);
			}
		}

		// Now it's required to sort, since we want
		// to perform binary search later on.
		table.Sort();
	}

	Vec<Entry>& EntryTable::GetEntries()
	{
		return entries;
	}
}