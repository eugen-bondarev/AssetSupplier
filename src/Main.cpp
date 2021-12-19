#include "ResourceManager.h"
#include "Test/Model.h"
#include "Exception.h"
#include "Package.h"
#include "Logging.h"

int main(int argc, char* argv[])
{
	const srm::String root{ "C:/Users/azare/Documents/Dev/Cpp/AssetSupplier/assets" };

	srm::ResourceManager resourceManager{ root, "myTableFile", "myDataFile", srm::ResourceManager::Mode::Create };
	srm::Resource resource;

	try
	{
		resource = resourceManager.Load("a/b/ddc");
	}
	catch (const srm::Exception& exception)
	{
		SRM_CONSOLE_OUT("[Error] %s", exception.what());
	}

	if (resource)
	{
		srm::String str{ "" };
		for (size_t i = 0; i < resource.data.size(); ++i)
		{
			str += resource.data[i];
		}
		SRM_CONSOLE_INFO(str);
	}

	//if (asset)
	//{
	//	Model model(asset);
	//	ASU_VAR(model.vertices.size());
	//	ASU_VAR(model.indices.size());
	//}

	return 0;
}