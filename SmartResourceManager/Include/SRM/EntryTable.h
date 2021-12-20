#pragma once

#include "Common.h"
#include "Entry.h"

namespace srm
{
	class EntryTable
	{
		friend void LoadEntryList(EntryTable& entryList, const String& path);
		friend void CreateEntryList(EntryTable& entryList, const String& root, const Vec<String>& ignoreFiles);

	public:
		Vec<Entry>& GetEntries();

		void ToFile(const String& path);

		void Sort();

		void SortByOffset();

	private:
		Vec<Entry> entries;
	};
}