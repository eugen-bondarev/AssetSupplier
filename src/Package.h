#pragma once

#include "Common.h"
#include "Entry.h"

namespace Asu
{
	class Package
	{
	public:
		Package(const String& rootDir);

		const Entry& GetEntry(const size_t i) const;

	private:
		void ProcessFile(String& path, size_t& offset);

		String rootDir;
		EntryTable entryTable;
	};
}