#include "Common.h"

// AssetManager = 
//		data0.asu, data1.asu, dataN.asu
// +
//		descriptor
//		Entry example:
// 
//		Assets/Models/Humanoid/Orc.fbx 5000000
//		GetLocation() const : string = "Assets/Models/Humanoid"
//		GetExtension() const: string = "fbx" -> Helps us find the corresponding importer
//		GetSize() const : size_t = 5000000

#include <filesystem>

#include <spdlog/spdlog.h>
// spdlog::set_pattern("%^%v%$"); // spdlog::set_pattern("[%^%l%$] %v");

#define ASU_LOG(...) spdlog::info(__VA_ARGS__)
#define ASU_WARN(...) spdlog::warn(__VA_ARGS__)
#define ASU_ERR(...) spdlog::error(__VA_ARGS__)

namespace Asu
{
	void ReplaceAll(std::string& string, const std::string& x, const std::string& y)
	{
		size_t pos;
		while ((pos = string.find(x)) != std::string::npos) 
		{
			string.replace(pos, 1, y);
		}
	}

	void PackFile(const std::string& rootDir, std::string& path)
	{
		ReplaceAll(path, "\\", "/");
		ASU_LOG("Processing path {0}", path);
	}

	void Pack(const std::string& rootDir)
	{
		namespace fs = std::filesystem;

		for (const auto& entry : fs::recursive_directory_iterator(rootDir))
		{
			if (entry.is_directory())
			{

			}
			else
			{
				PackFile(rootDir, entry.path().string());
			}
		}
	}
}

int main()
{
	spdlog::set_pattern("[%^%l%$] %v");
	Asu::Pack("C:/Users/azare/Documents/Dev/Cpp/AssetSupplier/assets");

	return 0;
}