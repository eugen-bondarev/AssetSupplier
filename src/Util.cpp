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

		String GetExtension(const String& fileName)
		{
			const size_t lastDot{ fileName.find_last_of(".") };
			const String extension{ fileName.substr(lastDot + 1, fileName.size() - lastDot) };
			return extension;
		}

		size_t GetFileSize(const String& path)
		{
			std::ifstream fileStream(path, std::ifstream::ate | std::ifstream::binary);
			return fileStream.tellg();
		}
	}
}