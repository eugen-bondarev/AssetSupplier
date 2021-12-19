#pragma once

#include <FileWatcher/FileWatcher.h>
#include "Common.h"

namespace srm
{
	class ResourceManager;

	// Processing file changes if the AssetSupplierFlags_Watch flag is set.
	class FileChangeListener : public FW::FileWatchListener
	{
	public:
		FileChangeListener(const String& root, FW::FileWatcher& watcher, ResourceManager& assetSupplier);

#pragma warning(disable: 26812)
		void handleFileAction(FW::WatchID watchID, const FW::String& directory, const FW::String& fileName, FW::Action action) override;
#pragma warning(default: 26812)

	private:
		const String& root;
		FW::FileWatcher& watcher;
		ResourceManager& assetSupplier;
	};
}