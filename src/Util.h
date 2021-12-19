#pragma once

#include "Common.h"

namespace srm
{
	namespace Util
	{
		String ReplaceAll(const String& string, const String& x, const String& y);

		String GetExtension(const String& fileName);

		size_t GetFileSize(const String& path);
	}
}