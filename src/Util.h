#pragma once

#include "Common.h"

namespace Asu
{
	namespace Util
	{
		String ReplaceAll(const String& string, const String& x, const String& y);

		size_t GetFileSize(const String& path);
	}
}