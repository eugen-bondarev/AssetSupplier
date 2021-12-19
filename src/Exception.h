#pragma once

#include <stdexcept>
#include "Common.h"

namespace Asu
{
	class Exception : public std::runtime_error
	{
	public:
		Exception(const String& message) 
			: std::runtime_error(message)
		{}
	};

	class EntryNotFound : public Exception
	{
	public:
		EntryNotFound() 
			: Exception("Entry not found.") 
		{}

		EntryNotFound(const String& entry) 
			: Exception("Entry not found: " + entry) 
		{}
	};
}