#include "Asset.h"

namespace Asu
{
	bool Asset::IsEmpty() const
	{
		return data.size() != 0;
	}
}