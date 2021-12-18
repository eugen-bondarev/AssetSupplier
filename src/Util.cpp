#include "Util.h"

#include <fstream>

namespace Asu
{
	namespace Util
	{
		String ReplaceAll(const String& string, const String& x, const String& y)
		{
			String result{ string };
			size_t pos;

			while ((pos = result.find(x)) != String::npos)
			{
				result.replace(pos, 1, y);
			}

			return result;
		}

		size_t GetFileSize(const String& path)
		{
			std::ifstream fileStream(path, std::ifstream::ate | std::ifstream::binary);
			return fileStream.tellg();
		}
	}
}