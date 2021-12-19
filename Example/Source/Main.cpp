#include <SRM/ResourceManager.h>
#include <SRM/Exception.h>
#include <SRM/Logging.h>

int main(const int argc, const char* argv[])
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

	return 0;
}