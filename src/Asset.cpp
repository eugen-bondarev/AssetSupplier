#include "Asset.h"
#include "Asset.h"

namespace Asu
{
	bool Asset::IsEmpty() const
	{
		return data.size() == 0;
	}

	Asset::operator bool() const
	{
		return !IsEmpty();
	}
}