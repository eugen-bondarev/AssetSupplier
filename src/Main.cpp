#include "AssetSupplier.h"
#include "Package.h"

int main()
{
	spdlog::set_pattern("[%^%l%$] %v");

	const Asu::String root{ "C:/Users/azare/Documents/Dev/Cpp/AssetSupplier/assets" };

	Asu::AssetSupplier assetSupplier{ root, Asu::AssetSupplierFlags_Create };

	Asu::Asset asset;
	assetSupplier.Load(asset, "foo/foo/MyFavoriteFile.file");

	ASU_INFO(asset.data.size());

	Asu::String data;
	for (size_t i = 0; i < asset.data.size(); ++i)
	{
		data += asset.data[i];
	}
	ASU_INFO(data);

	return 0;
}