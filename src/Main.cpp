#include "AssetSupplier.h"
#include "Test/Model.h"
#include "Package.h"

int main()
{
	spdlog::set_pattern("[%^%l%$] %v");

	const Asu::String root{ "C:/Users/azare/Documents/Dev/Cpp/AssetSupplier/assets" };

	Asu::AssetSupplier assetSupplier{ root, Asu::AssetSupplierFlags_None };

	Asu::Asset asset;
	assetSupplier.Load(asset, "CharacterModel.fbx");

	Model model(asset);

	ASU_VAR(model.vertices.size());
	ASU_VAR(model.indices.size());

	//ASU_INFO(asset.data.size());

	//Asu::String data;
	//for (size_t i = 0; i < asset.data.size(); ++i)
	//{
	//	data += asset.data[i];
	//}
	//ASU_INFO(data);

	return 0;
}