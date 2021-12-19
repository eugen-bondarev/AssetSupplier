#include "AssetSupplier.h"

#include "FileChangeListener.h"

namespace Asu
{
	// This gets initialized before using Asu (Setting up the formatting method).
	struct Initializer
	{
		Initializer()
		{
			spdlog::set_pattern("[%^%l%$] %v");
		}
	} initializer;



	void AssetSupplier::OnFlagCreate()
	{
		CreateEntryTable(table, root, ignoreFiles);
		EntryTableToFile(root + "/" + tableFileName, table);
		AssetsToFile(root + "/" + dataFileName, root, table);
	}

	void AssetSupplier::OnFlagNone()
	{
		EntryTableFromFile(table, root + "/" + tableFileName);
	}

	AssetSupplier::AssetSupplier(
		const String& root, 
		const String& tableFileName,
		const String& dataFileName,
		const AssetSupplierFlags flags
	) : root{ root }, tableFileName{ tableFileName }, dataFileName{ dataFileName }
	{
		ignoreFiles.resize(2);
		ignoreFiles[0] = tableFileName;
		ignoreFiles[1] = dataFileName;

		if (flags & AssetSupplierFlags_Create)
		{
			OnFlagCreate();
		}
		else
		{
			OnFlagNone();
		}

		if (flags & AssetSupplierFlags_Watch)
		{
			FW::FileWatcher watcher;
			FileChangeListener listener{ root, watcher, *this };
			watcher.addWatch(root, &listener, true);

			// Todo: Make it in a separate thread.
			while (true)
			{
				watcher.update();
			}
		}
	}

	Asset AssetSupplier::Load(const String& location)
	{
		Asset asset;
		const Entry& entry{ FindEntry(location) };
		LoadAsset(asset, root + "/" + dataFileName, entry);
		return asset;
	}

	bool AssetSupplier::IsFileIgnored(const String& fileName) const
	{
		return std::find(
			std::begin(ignoreFiles),
			std::end(ignoreFiles),
			fileName
		) != std::end(ignoreFiles);
	}

	const Entry& AssetSupplier::FindEntry(const String& location)
	{
		for (size_t i = 0; i < table.size(); ++i)
		{
			if (table[i].GetLocation() == location)
			{
				return table[i];
			}
		}

		// throw
	}
}