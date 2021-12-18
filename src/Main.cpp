#include "AssetSupplier.h"
#include "Test/Model.h"
#include "Package.h"

int main()
{
	const Asu::String root{ "C:/Users/azare/Documents/Dev/Cpp/AssetSupplier/assets" };

	Asu::AssetSupplier assetSupplier{ root, Asu::AssetSupplierFlags_None };

	Asu::Asset asset = assetSupplier.Load("CharacterModel.fbx");
	
	// Test loaded data
	Model model(asset);
	ASU_VAR(model.vertices.size());
	ASU_VAR(model.indices.size());

	return 0;
}