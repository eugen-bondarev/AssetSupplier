#pragma once

#include "Common.h"

namespace Asu
{
	// The entity that gets loaded by the library.
	struct Asset
	{
		// Bytes.
		Vec<char> data;

		// Returns true if the entity wasn't loaded properly.
		bool IsEmpty() const;
	};
}