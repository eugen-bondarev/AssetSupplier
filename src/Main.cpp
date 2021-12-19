#include "AssetSupplier.h"
#include "Test/Model.h"
#include "Exception.h"
#include "Package.h"
#include "Logging.h"

int main(int argc, char* argv[])
{
	//ASU_CONSOLE_INFO(COLOR_GREEN_START "Info" COLOR_GREEN_END);

	const Asu::String root{ "C:/Users/azare/Documents/Dev/Cpp/AssetSupplier/assets" };

	Asu::AssetSupplier assetSupplier{ root, "myTableFile", "myDataFile", Asu::AssetSupplierFlags_Create };
	Asu::Asset asset;

	try
	{
		asset = assetSupplier.Load("a/b/ddc");
	}
	catch (const Asu::Exception& exception)
	{
		ASU_CONSOLE_OUT("[Error] %s", exception.what());
	}

	if (asset)
	{
		Asu::String str{ "" };
		for (size_t i = 0; i < asset.data.size(); ++i)
		{
			str += asset.data[i];
		}
		ASU_CONSOLE_INFO(str);
		//ASU_CONSOLE_VAR(str);
		//ASU_VAR(str);
	}

	//if (asset)
	//{
	//	Model model(asset);
	//	ASU_VAR(model.vertices.size());
	//	ASU_VAR(model.indices.size());
	//}

	return 0;
}