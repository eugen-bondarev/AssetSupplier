#include "AssetSupplier.h"

#include <FileWatcher/FileWatcher.h>
#include "Util.h"

namespace Asu
{
	// Processing file changes if the AssetSupplierFlags_Watch flag is set.
	class AsuListener : public FW::FileWatchListener
	{
	public:
		AsuListener(const String& root, FW::FileWatcher& watcher, AssetSupplier& assetSupplier) : root{ root }, watcher { watcher }, assetSupplier{ assetSupplier }
		{
		}

#pragma warning(disable: 26812)
		void handleFileAction(FW::WatchID watchID, const FW::String& directory, const FW::String& fileName, FW::Action action) override
		{
			if (Util::GetExtension(fileName) == "asu") return;

			assetSupplier.OnFlagCreate();
			ASU_INFO("{0}/{1}", directory, fileName);
		}
#pragma warning(default: 26812)

	private:
		const String& root;
		FW::FileWatcher& watcher;
		AssetSupplier& assetSupplier;
	};



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
		CreateEntryTable(table, root);
		EntryTableToFile(root + "/table.asu", table);
		AssetsToFile(root + "/data.asu", root, table);
	}

	void AssetSupplier::OnFlagNone()
	{
		EntryTableFromFile(table, root + "/table.asu");
	}

	AssetSupplier::AssetSupplier(const String& root, const AssetSupplierFlags flags) : root{ root }
	{
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
			AsuListener listener{ root, watcher, *this };
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
		LoadAsset(asset, root + "/data.asu", entry);
		return asset;
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