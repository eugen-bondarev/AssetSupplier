#include <SRM/SRM.h>

#ifndef EXAMPLE_ROOT_DIR
#	define EXAMPLE_ROOT_DIR
#endif

int main(const int argc, const char* argv[])
{
	const srm::String root{ EXAMPLE_ROOT_DIR "/Assets" };

	srm::ResourceManager resourceManager{ 
		root, 
		"table.asu", 
		"data.asu", 
		srm::ResourceManager::Mode::Create 
	};

	srm::Resource resource;

	try
	{
		//resource = resourceManager.Load("a/b/c/d/e/deep-file.deep");
		resource = resourceManager.Load("a/new-file.file");
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