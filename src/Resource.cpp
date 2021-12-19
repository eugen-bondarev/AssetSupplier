#include "Resource.h"

namespace srm
{
	bool Resource::IsEmpty() const
	{
		return data.size() == 0;
	}

	Resource::operator bool() const
	{
		return !IsEmpty();
	}
}