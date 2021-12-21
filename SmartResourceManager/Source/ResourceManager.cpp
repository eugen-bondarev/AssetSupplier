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
	void ResourceManager::OnFlagCreate()
	{
		entryTable.Create(root, ignoreFiles);
		entryTable.CreateTableFile(root + "/" + tableFileName);
		entryTable.CreateDataFile(root + "/" + dataFileName, root);
	}

	void ResourceManager::OnFlagNone()
	{
		entryTable.Load(root + "/" + tableFileName);
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
		// Binary search.
		const Entry copy{ location, 0, 0 };

		auto it = std::lower_bound(
			entryTable.entries.begin(),
			entryTable.entries.end(),
			copy,
			[](const Entry & a, const Entry & b)
			{
				return a.GetLocation() < b.GetLocation();
			}
		);

		if (it->GetLocation() != location)
		{
			throw EntryNotFound(location);
		}
		else
		{
			const size_t index{ static_cast<size_t>(std::distance(entryTable.entries.begin(), it)) };
			return entryTable.entries[index];
		}
	}
}