#pragma once

#include <assert.h>
#define SRM_ASSET(x) assert(x)

#include <vector>
#include <string>
#include <map>

#define SRM_API __declspec(dllexport)

namespace srm
{
	template <typename T>
	using Vec = std::vector<T>;
	
	using String = std::string;

	using Flags = uint32_t;
}