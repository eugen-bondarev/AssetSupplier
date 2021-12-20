#include <SRM/SRM.h>

#include <algorithm>

#ifndef EXAMPLE_ROOT_DIR
#	define EXAMPLE_ROOT_DIR
#endif

namespace srm
{
	class ModelAsset
	{
	public:
		ModelAsset(const srm::Resource& resource)
		{
		}
	};
}

int main(const int argc, const char* argv[])
{
	const srm::String root{ EXAMPLE_ROOT_DIR "/Assets" };

	srm::ResourceManager resourceManager{ root, "table.asu", "data.asu", srm::ResourceManager::Mode::Create };
	srm::Resource resource;

	//struct MyModelAsset
	//{
	//	MyModelAsset(const srm::Resource& resource)
	//	{
	//		SRM_CONSOLE_INFO("Calling constructor model");
	//	}
	//};

	//struct MyImageAsset
	//{
	//	MyImageAsset(const srm::Resource& resource)
	//	{
	//		SRM_CONSOLE_INFO("Calling constructor image");
	//	}
	//};

	//srm::Cache<MyModelAsset> modelCache(resourceManager);
	//srm::Cache<MyImageAsset> imageCache(resourceManager);

	//const MyModelAsset& model0 = modelCache.Load("a/b/ddc");
	//const MyModelAsset& model1 = modelCache.Load("a/b/ddc");
	//const MyImageAsset& image0 = imageCache.Load("a/b/OtherShader.frag");
	//const MyImageAsset& image1 = imageCache.Load("a/b/OtherShader.frag");

	try
	{
		resource = resourceManager.Load("a/b/ddd");
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