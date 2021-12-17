#include "Util.h"

#include <fstream>

namespace Asu
{
	namespace Util
	{
		void ReplaceAll(String& string, const String& x, const String& y)
		{
			size_t pos;
			while ((pos = string.find(x)) != String::npos)
			{
				string.replace(pos, 1, y);
			}
		}

		size_t GetFileSize(const String& path)
		{
			std::ifstream fileStream(path, std::ifstream::ate | std::ifstream::binary);
			return fileStream.tellg();
		}
	}
}