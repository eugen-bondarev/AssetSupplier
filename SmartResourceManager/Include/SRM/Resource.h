#pragma once

#include "Common.h"

namespace srm
{
	// The entity that gets loaded by the library.
	struct SRM_API Resource
	{
		// Bytes.
		Vec<char> data;

		// Returns true if the entity wasn't loaded properly.
		bool IsEmpty() const;

		// Is not empty.
		operator bool() const;
	};
}