#include <SRM/SRM.h>

#include <algorithm>

#ifndef EXAMPLE_ROOT_DIR
#	define EXAMPLE_ROOT_DIR
#endif

int main(const int argc, const char* argv[])
{
	const srm::String root{ EXAMPLE_ROOT_DIR "/Assets" };

	srm::ResourceManager resourceManager{ root, "table.asu", "data.asu", srm::ResourceManager::Mode::Create };
	srm::Resource resource;

	//srm::Cache<ImageAsset> imageCache(resourceManager);
	//const ImageAsset& imageAsset = imageCache.Load("CharacterTexture.png");
	//const MyImageAsset& image0 = imageCache.Load("a/b/OtherShader.frag");
	//const MyImageAsset& image1 = imageCache.Load("a/b/OtherShader.frag");

	try
	{
		resource = resourceManager.Load("a/c/e/Fa.vert");
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