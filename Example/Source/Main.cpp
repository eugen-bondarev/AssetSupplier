#include <SRM/SRM.h>

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

	template <typename T>
	class Cache
	{
	public:
		using UserDefinedResource = T;
		using Storage = Map<String, Ptr<UserDefinedResource>>;

		Cache(ResourceManager& manager) 
			: manager{ manager }
		{
		}

		virtual ~Cache() = default;

		const UserDefinedResource& Load(const String& path)
		{
			const Storage::const_iterator iterator = entities.find(path);

			if (iterator != std::end(entities))
			{
				const UserDefinedResource& item{ *iterator->second };
				return item;
			}

			const Resource resource{ manager.Load(path) };
			UserDefinedResource* item{ new UserDefinedResource(resource) };
			entities[path] = Ptr<UserDefinedResource>(item);
			return *item;
		}

	protected:
		ResourceManager& manager;
		Storage entities;

	private:
		Cache(const Cache&) = delete;
		Cache& operator=(const Cache&) = delete;
	};
}

int main(const int argc, const char* argv[])
{
	const srm::String root{ EXAMPLE_ROOT_DIR "/Assets" };

	srm::ResourceManager resourceManager{ root, "table.asu", "data.asu", srm::ResourceManager::Mode::Create };
	srm::Resource resource;

	struct MyModelAsset
	{
		MyModelAsset(const srm::Resource& resource)
		{
			SRM_CONSOLE_INFO("Calling constructor");
		}
	};

	struct MyImageAsset
	{
		MyImageAsset(const srm::Resource& resource)
		{
			SRM_CONSOLE_INFO("Calling constructor");
		}
	};

	srm::Cache<MyModelAsset> modelCache(resourceManager);
	srm::Cache<MyImageAsset> imageCache(resourceManager);

	const MyModelAsset& model0 = modelCache.Load("a/b/ddc");
	const MyModelAsset& model1 = modelCache.Load("a/b/ddc");

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