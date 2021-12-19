#pragma once

#include <assert.h>
#define ASU_ASSERT(x) assert(x)

//#include <spdlog/spdlog.h>
//#define ASU_INFO(...) spdlog::info(__VA_ARGS__)
//#define ASU_WARN(...) spdlog::warn(__VA_ARGS__)
//#define ASU_ERR(...) spdlog::error(__VA_ARGS__)
//#define ASU_VAR(x) ASU_INFO(#x " = {0}", x)

#include <vector>
#include <string>
#include <map>

namespace Asu
{
	template <typename T>
	using Vec = std::vector<T>;
	
	using String = std::string;

	using Flags = uint32_t;
}