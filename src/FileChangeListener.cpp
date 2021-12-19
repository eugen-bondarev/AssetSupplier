#include "FileChangeListener.h"

#include "ResourceManager.h"
#include "Logging.h"

namespace srm
{
	FileChangeListener::FileChangeListener(
		const String& root, 
		FW::FileWatcher& watcher, 
		ResourceManager& assetSupplier
	) : root{ root }, watcher{ watcher }, assetSupplier{ assetSupplier }
	{
	}

#pragma warning(disable: 26812)
	void FileChangeListener::handleFileAction(
		FW::WatchID watchID, 
		const FW::String& directory, 
		const FW::String& fileName, 
		FW::Action action
	)
	{
		if (assetSupplier.IsFileIgnored(fileName)) return;

		assetSupplier.OnFlagCreate();
		SRM_CONSOLE_INFO("%s/%s", directory.c_str(), fileName.c_str());
	}
#pragma warning(default: 26812)
}