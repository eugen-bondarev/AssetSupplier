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
	void AssetsToFile(const String& path, const String& pathPrefix, const EntryTable& table)
	{
		std::ofstream outputStream{ path, std::ios::binary };

		EntryTable sorted{ table };

		// We need to sort the table by offset before storing it.
		sorted.SortByOffset();

		for (size_t i = 0; i < sorted.GetEntries().size(); ++i)
		{
			const String currentFileFullPath{ pathPrefix + "/" + sorted.GetEntries()[i].GetLocation() };
			std::ifstream currentFile{ currentFileFullPath, std::ios::binary };
			outputStream << currentFile.rdbuf();
		}
	}

	void ResourceManager::OnFlagCreate()
	{
		CreateEntryList(table, root, ignoreFiles);
		table.ToFile(root + "/" + tableFileName);

		AssetsToFile(root + "/" + dataFileName, root, table);
	}

	void ResourceManager::OnFlagNone()
	{
		LoadEntryList(table, root + "/" + tableFileName);
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
		// Binary search
		const Entry copy{ location, 0, 0 };
		const size_t index = static_cast<size_t>(std::lower_bound(
			std::begin(table.GetEntries()),
			std::end(table.GetEntries()),
			copy,
			[](const Entry& a, const Entry& b)
			{
				return a.GetLocation() < b.GetLocation();
			}
		) - std::begin(table.GetEntries()));

		if (index == Util::invalidIndex)
		{
			throw EntryNotFound(location);
			return table.GetEntries()[0];
		}

		return table.GetEntries()[index];
	}
}