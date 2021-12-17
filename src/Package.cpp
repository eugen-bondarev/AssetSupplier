#include "Package.h"

#include <filesystem>
#include <fstream>
#include "Util.h"

namespace Asu
{
	Package::Package(const String& rootDir) : rootDir{ rootDir }
	{
		Util::ReplaceAll(this->rootDir, "\\", "/");
		ASU_INFO("Root dir: {0}", rootDir);
		size_t offset{ 0 };
		for (const auto& entry : std::filesystem::recursive_directory_iterator(rootDir))
		{
			if (!entry.is_directory())
			{
				ProcessFile(entry.path().string(), offset);
			}
		}
		SerializeEntryTable(rootDir + "/table.asu", entryTable);
	}

	void Package::ProcessFile(String& fullPath, size_t& offset)
	{
		Util::ReplaceAll(fullPath, "\\", "/");
		const String localPath{ fullPath.substr(rootDir.size() + 1, fullPath.size() - rootDir.size()) };
		const size_t size{ Util::GetFileSize(fullPath) };
		if (size != 0)
		{
			entryTable.emplace_back(localPath, size, offset);
		}
		else
		{
			ASU_WARN("Skipped file: {0}", localPath);
		}
	}
}