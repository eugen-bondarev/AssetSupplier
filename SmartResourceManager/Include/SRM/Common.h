#pragma once

#include <assert.h>
#define SRM_ASSET(x) assert(x)

#include <vector>
#include <string>
#include <memory>
#include <map>

#define SRM_API __declspec(dllexport)

namespace srm
{
	template <typename T>
	using Vec = std::vector<T>;
	
	using String = std::string;

	using Flags = uint32_t;

	template <typename First, typename Second>
	using Map = std::map<First, Second>;

	template <typename T>
	using Ptr = std::unique_ptr<T>;

	template <typename T, typename... Args>
	auto CreatePtr(Args&&... args) -> decltype(std::make_unique<T>(std::forward<Args&&>(args)...))
	{
		return std::make_unique<T>(std::forward<Args&&>(args)...);
	}
}