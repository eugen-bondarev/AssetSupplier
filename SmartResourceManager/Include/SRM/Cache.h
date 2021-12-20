#pragma once

#include "ResourceManager.h"
#include "Resource.h"
#include "Common.h"

#include <limits>

namespace srm
{
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