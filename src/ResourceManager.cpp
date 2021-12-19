#include "ResourceManager.h"

#include "FileChangeListener.h"
#include "Exception.h"

namespace srm
{
	// This gets initialized before using Asu (Setting up the formatting method).
	struct Initializer
	{
		Initializer()
		{
			//spdlog::set_pattern("[%^%l%$] %v");
		}
	} initializer;



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
		for (size_t i = 0; i < table.size(); ++i)
		{
			if (table[i].GetLocation() == location)
			{
				return table[i];
			}
		}

		throw EntryNotFound(location);
	}
}