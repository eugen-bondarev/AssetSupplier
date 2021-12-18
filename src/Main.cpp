#include "Package.h"

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

int main()
{
	spdlog::set_pattern("[%^%l%$] %v");
	Asu::Package package("C:/Users/azare/Documents/Dev/Cpp/AssetSupplier/assets");

	Asu::Asset asset;
	Asu::LoadAsset(asset, "C:/Users/azare/Documents/Dev/Cpp/AssetSupplier/assets/data.asu", package.GetEntry(2));

	ASU_INFO(asset.data.size());

	Asu::String data;
	for (size_t i = 0; i < asset.data.size(); ++i)
	{
		data += asset.data[i];
	}
	ASU_INFO(data);

	return 0;
}