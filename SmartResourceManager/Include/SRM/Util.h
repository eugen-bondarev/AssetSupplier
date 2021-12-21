#pragma once

#include "Common.h"

#include <limits>

namespace srm
{
	namespace Util
	{
		inline static constexpr size_t invalidIndex{ std::numeric_limits<size_t>::max() };

		String ReplaceAll(const String& string, const String& x, const String& y);

		String GetExtension(const String& fileName);

		size_t GetFileSize(const String& path);

		template <typename T>
		size_t BinarySearchIndexOf(const Vec<T>& vector, const T& item)
		{			
			const size_t index{ static_cast<size_t>(std::lower_bound(
				std::begin(vector),
				std::begin(end),
				item
			) - std::begin(vector)) };
			return index < vector.size() ? index : invalidIndex;
		}
	}
}