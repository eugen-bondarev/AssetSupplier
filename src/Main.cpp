#include "AssetSupplier.h"
#include "Test/Model.h"
#include "Package.h"

int main()
{
	const Asu::String root{ "C:/Users/azare/Documents/Dev/Cpp/AssetSupplier/assets" };

	Asu::AssetSupplier assetSupplier{ root, Asu::AssetSupplierFlags_Create };

	Asu::Asset asset = assetSupplier.Load("foo/foo/aa");

	Asu::String str{ "" };
	for (size_t i = 0; i < asset.data.size(); ++i)
	{
		str += asset.data[i];
	}
	ASU_VAR(str);
	
	// Test loaded data
	//Model model(asset);
	//ASU_VAR(model.vertices.size());
	//ASU_VAR(model.indices.size());

	return 0;
}