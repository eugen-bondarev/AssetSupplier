#include "Package.h"

#include <filesystem>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Util.h"

namespace Asu
{
	static void AppendToEntryTable(Entries& table, const String& root, const String& pathWithMessySlashes, size_t& offset)
	{
		const String fullPath = Util::ReplaceAll(pathWithMessySlashes, "\\", "/");

		const String localPath{ fullPath.substr(root.size() + 1, fullPath.size() - root.size()) };
		const size_t size{ Util::GetFileSize(fullPath) };

		const Entry entry{ localPath, size, offset };

		if (entry.GetSize() != 0 && entry.GetExtension() != "asu")
		{
			table.push_back(entry);
			offset += size;
		}
		else
		{
			ASU_WARN("Skipping file: {0}", localPath);
		}
	}

	void CreateEntryTable(Entries& table, const String& root)
	{
		ASU_INFO("Creating entry table: {0}", root);

		size_t offset{ 0 };

		table.clear();

		for (const auto& entry : std::filesystem::recursive_directory_iterator(root))
		{
			if (!entry.is_directory())
			{
				AppendToEntryTable(table, root, entry.path().string(), offset);
			}
		}

		std::sort(
			std::begin(table), 
			std::end(table), 
			[&](const Entry& a, const Entry& b) 
			{ 
				return a.GetLocation() < b.GetLocation();
			}
		);
	}

	static void LineToEntry(Entry& entry, const String& line)
	{
		std::istringstream stringStream(line);

		String name{ "" };
		size_t size{ 0 };
		size_t offset{ 0 };

		stringStream >> name >> size >> offset;

		entry.SetLocation(name);
		entry.SetSize(size);
		entry.SetOffset(offset);
	}

	void EntryTableFromFile(Entries& table, const String& path)
	{
		std::ifstream inputStream{ path };
		String line;

		table.clear();

		while (std::getline(inputStream, line))
		{
			Entry entry;
			LineToEntry(entry, line);
			table.push_back(entry);
		}
	}

	void EntryTableToFile(const String& path, const Entries& table)
	{
		std::ofstream outputStream{ path };

		for (size_t i = 0; i < table.size(); i++)
		{
			outputStream << table[i].GetLocation() << ' ' << table[i].GetSize() << ' ' << table[i].GetOffset();
			if (i != table.size() - 1)
			{
				outputStream << '\n';
			}
		}
	}

	void AssetsToFile(const String& path, const String& pathPrefix, const Entries& table)
	{
		std::ofstream outputStream{ path, std::ios::binary };

		for (size_t i = 0; i < table.size(); ++i)
		{
			const String currentFileFullPath{ pathPrefix + "/" + table[i].GetLocation() };
			std::ifstream currentFile{ currentFileFullPath, std::ios::binary };
			outputStream << currentFile.rdbuf();
		}
	}

	void Pack(const String& rootWithMessySlashes)
	{
		Entries table;
		const String root{ Util::ReplaceAll(rootWithMessySlashes, "\\", "/") };
		CreateEntryTable(table, root);
		EntryTableToFile(root + "/table.asu", table);
		AssetsToFile(root + "/data.asu", root, table);
	}
}