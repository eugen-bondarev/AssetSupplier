#include "ResourceManager.h"

#include "FileChangeListener.h"
#include "Exception.h"
#include "Logging.h"
#include "Util.h"

#include <filesystem>
#include <algorithm>
#include <sstream>
#include <fstream>

namespace srm
{
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
			table.push_back(entry);
			offset += size;
		}
		else
		{
			SRM_CONSOLE_WARN("Skipping file: %s", localPath.c_str());
		}
	}

	static void SortAlphabetically(EntryTable& table)
	{
		std::sort(
			std::begin(table),
			std::end(table),
			[&](const Entry& a, const Entry& b)
			{
				return a.GetLocation() < b.GetLocation();
			}
		);
	}

	void CreateEntryTable(EntryTable& table, const String& root, const Vec<String>& ignoreFiles)
	{
		SRM_CONSOLE_INFO("Creating entry table: %s", root.c_str());

		size_t offset{ 0 };

		table.clear();

		for (const auto& entry : std::filesystem::recursive_directory_iterator(root))
		{
			if (!entry.is_directory())
			{
				AppendToEntryTable(table, root, entry.path().string(), offset, ignoreFiles);
			}
		}

		// Now it's required to sort, since we want
		// to perform binary search later on.
		SortAlphabetically(table);
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

	void EntryTableFromFile(EntryTable& table, const String& path)
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

	void EntryTableToFile(const String& path, const EntryTable& table)
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

	void AssetsToFile(const String& path, const String& pathPrefix, const EntryTable& table)
	{
		std::ofstream outputStream{ path, std::ios::binary };

		EntryTable sorted{ table };

		// We need to sort the table by offset before storing it.
		std::sort(
			std::begin(sorted),
			std::end(sorted),
			[](const Entry& a, const Entry& b)
			{
				return a.GetOffset() < b.GetOffset();
			}
		);

		for (size_t i = 0; i < sorted.size(); ++i)
		{
			const String currentFileFullPath{ pathPrefix + "/" + sorted[i].GetLocation() };
			std::ifstream currentFile{ currentFileFullPath, std::ios::binary };
			outputStream << currentFile.rdbuf();
		}
	}






	void ResourceManager::OnFlagCreate()
	{
		CreateEntryTable(table, root, ignoreFiles);
		EntryTableToFile(root + "/" + tableFileName, table);
		AssetsToFile(root + "/" + dataFileName, root, table);
	}

	void ResourceManager::OnFlagNone()
	{
		EntryTableFromFile(table, root + "/" + tableFileName);
	}

	ResourceManager::ResourceManager(
		const String& root, 
		const String& tableFileName,
		const String& dataFileName,
		const Mode mode
	) : root{ root }, tableFileName{ tableFileName }, dataFileName{ dataFileName }
	{
		ignoreFiles.resize(2);
		ignoreFiles[0] = tableFileName;
		ignoreFiles[1] = dataFileName;

		switch (mode)
		{
			case Mode::Create:
			{
				OnFlagCreate();
				break;
			}
			case Mode::Default:
			{
				OnFlagNone();
				break;
			}
			case Mode::Watch:
			{
				FW::FileWatcher watcher;
				FileChangeListener listener{ root, watcher, *this };
				watcher.addWatch(root, &listener, true);

				// Todo: Make it in a separate thread.
				while (true)
				{
					watcher.update();
				}
				break;
			}
		}
	}

	Resource ResourceManager::Load(const String& location)
	{
		Resource asset;
		const Entry& entry{ FindEntry(location) };
		LoadAsset(asset, root + "/" + dataFileName, entry);
		return asset;
	}

	bool ResourceManager::IsFileIgnored(const String& fileName) const
	{
		return std::find(
			std::begin(ignoreFiles),
			std::end(ignoreFiles),
			fileName
		) != std::end(ignoreFiles);
	}

	const Entry& ResourceManager::FindEntry(const String& location)
	{
		//for (size_t i = 0; i < table.size(); ++i)
		//{
		//	if (table[i].GetLocation() == location)
		//	{
		//		return table[i];
		//	}
		//}

		const Entry copy{ location, 0, 0 };
		const size_t index = static_cast<size_t>(std::lower_bound(
			std::begin(table),
			std::end(table),
			copy,
			[](const Entry& a, const Entry& b)
			{
				return a.GetLocation() < b.GetLocation();
			}
		) - std::begin(table));

		if (index == Util::invalidIndex)
		{
			throw EntryNotFound(location);
			return table[0];
		}

		return table[index];
	}
}